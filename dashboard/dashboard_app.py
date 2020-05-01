import datetime

import dash
import time
import pandas as pd
import os
import dash_core_components as dcc
import dash_html_components as html
import plotly
import flask
from dash.dependencies import Input, Output
from sens_sim import fake_sim

live_font_size  = 70
live_font_px    = str(live_font_size) + "px"

lineh1      = '15px'
lineh2      = '85px'

good_color  = '#90EE90'

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

"""
Data is transmitted, comma-seperated, in the following order
-Time/date
-Inspiratory Pressure (cmh20)
-Exspiratory Pressure (cmh20)
-Inspiratory Flow Rate (SLPM)
-Exspiratory Flow Rate (SLPM)
-Inspiratory Volume (L)
-Expiratory Volume (L)
Mode (0: timed, 1: pressure-triggered)
Then if:
mode=0:(timed)
    -Inspiratory/expiratory ratio
    -Breaths per minute
mode=1:(pressure-triggered)
    -Maximum expiratory time
    -Inspiratory time
    -Pressure threshold

"""
sim = fake_sim('baba')

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    html.Div([
        html.H2('gVent Monitoring Dashboard'),
        html.Div(id='live-update-text', className="row"),
        dcc.Graph(id='live-update-graph'),
        html.H6('X axis'),
        dcc.Dropdown(
        id='xaxis-dropdown',
            options=[
                {'label': '1m', 'value': 60},
                {'label': '5m', 'value': 300},
                {'label': '15m', 'value': 900},
                {'label': '1h', 'value': 3600},
                {'label': '6h', 'value': 21600}
            ],
            value=60
        ),
        dcc.Interval(
            id='interval-component',
            interval=1000, # in milliseconds
            n_intervals=0
        ),
        html.Div(id='mode-text'),
        html.A(id='download-link', children='Download File')
    ])
)

data = {
    'Time': [],
    'Inspiratory Flow Rate': [],
    'Expiratory Flow Rate': [],
    'Inspiratory Pressure': [],
    'Expiratory Pressure': [],
    'Inspiratory Tidal Volume': [],
    'Expiratory Tidal Volume': [],
    'Mode': [],
    'Inspiratory/Expiratory Ratio': [],
    'Breaths per Minute': [],
    'Maximum Expiratory Time': [],
    'Inspiratory Time': [],
    'Pressure Threshold': []
}

@app.callback(Output('mode-text', 'children'),
              [Input('interval-component', 'n_intervals')])
def update_mode_text(n):
    if len(data['Mode']) == 0:
        return html.H5(' ')
    mode = data['Mode'][-1]
    if not mode:
        retstr = "Timed mode."
        retstr += "    IE Ratio: " + str(data['Inspiratory/Expiratory Ratio'][-1])
        retstr += "    BPM: " + str(data['Breaths per Minute'][-1])
    else:
        retstr = "Pressure-triggered mode."
        retstr += "    Max. Ex. time (ms): " + str(data['Maximum Expiratory Time'][-1])
        retstr += "    Ins. time (ms): " + str(data['Inspiratory Time'][-1])
        retstr += "    Pressure thresh (cmH2O): " + str(data['Pressure Threshold'][-1])
    return html.H4(retstr)


@app.callback(Output('live-update-text', 'children'),
              [Input('interval-component', 'n_intervals')])
def update_metrics(n):
    # Collect some data

    time = datetime.datetime.now()
    sensor_data = sim.readline()
    sensor_words = sensor_data.split(', ')

    ins_pres    = float(sensor_words[0])
    ex_pres     = float(sensor_words[1])
    ins_fr      = float(sensor_words[2])
    ex_fr       = float(sensor_words[3])
    ins_vol     = float(sensor_words[4])
    ex_vol      = float(sensor_words[5])

    mode        = int(sensor_words[6])

    if (mode==0): # if we're in timed mode
        ie_rat      = float(sensor_words[7])
        bpm         = float(sensor_words[8])
        max_ex_t    = None
        ins_t       = None
        pres_thresh = None
    else: # in pressure triggered mode
        max_ex_t    = int(sensor_words[7])
        ins_t       = int(sensor_words[8])
        pres_thresh = float(sensor_words[9])
        ie_rat      = None
        bpm         = None

    data['Time'].append(time)

    data['Inspiratory Flow Rate'].append(ins_fr)
    data['Inspiratory Pressure'].append(ins_pres)
    data['Inspiratory Tidal Volume'].append(ins_vol)

    data['Expiratory Flow Rate'].append(ex_fr)
    data['Expiratory Pressure'].append(ex_pres)
    data['Expiratory Tidal Volume'].append(ex_vol)

    data['Mode'].append(mode)
    data['Inspiratory/Expiratory Ratio'].append(ie_rat)
    data['Breaths per Minute'].append(bpm)
    data['Maximum Expiratory Time'].append(max_ex_t)
    data['Inspiratory Time'].append(ins_t)
    data['Pressure Threshold'].append(pres_thresh)

    ins_pres_col    = good_color
    ex_pres_col     = good_color
    ins_fr_col      = good_color
    ex_fr_col       = good_color
    ins_vol_col     = good_color
    ex_vol_col      = good_color

    style = {'padding': '0px', 'fontSize': '16px'}
    #TODO: make this all a table instead
    return [
        html.Div([
            html.H5('Ins. Fl. RT. (SLPM)', style={'lineHeight': lineh1}),
            html.Span('{0:.2f}'.format(ins_fr), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ins_pres_col}),
        html.Div([
            html.H5('Ins. Pres. (cmH20)', style={'lineHeight': lineh1}),
            html.Span('{0:.2f}'.format(ins_pres), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ins_fr_col}),
        html.Div([
            html.H5('Ins. Vol. (L)', style={'lineHeight': lineh1}),
            html.Span('{0:0.3f}'.format(ins_vol), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ex_fr_col}),
        html.Div([
            html.H5('Ex. Fl. RT. (SLPM)', style={'lineHeight': lineh1}),
            html.Span('{0:.2f}'.format(ex_fr), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ins_vol_col}),
        html.Div([
            html.H5('Ex. Pres. (cmH20)', style={'lineHeight': lineh1}),
            html.Span('{0:.2f}'.format(ex_pres), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ex_vol_col}),
        html.Div([
            html.H5('Ex. Vol. (L)', style={'lineHeight': lineh1}),
            html.Span('{0:0.3f}'.format(ex_vol), style={'fontSize': live_font_px, 'lineHeight': lineh2})
        ], className="two columns", style={'backgroundColor': ex_pres_col})
    ]

def make_csv():
    f = open('temp.csv', 'w')

    # csv header
    f.write("Time, \
    Inspiratory Pressure (cmH20), \
    Expiratory Pressure (cmH20), \
    Inspiratory Flow Rate (SLPM), \
    Expiratory Flow Rate (SLPM), \
    Inspiratory Tidal Volume (L), \
    Expiratory Tidal Volume (L), \
    Mode, \
    IE ratio, \
    BPM, \
    Maximum Expiratory Time (ms), \
    Inspiratory Time (ms), \
    Pressure Threshold (cmH20)")

    for i in range(len(data['Time'])):
        wstr = '\n'
        wstr += data['Time'][i].strftime("%d-%b-%Y %H:%M:%S.%f") + ', '
        wstr += str(data['Inspiratory Pressure'][i]) + ', '
        wstr += str(data['Expiratory Pressure'][i]) + ', '
        wstr += str(data['Inspiratory Flow Rate'][i]) + ', '
        wstr += str(data['Expiratory Flow Rate'][i]) + ', '
        wstr += str(data['Inspiratory Tidal Volume'][i]) + ', '
        wstr += str(data['Expiratory Tidal Volume'][i]) + ', '
        wstr += str(data['Mode'][i]) + ', '
        wstr += str(data['Inspiratory/Expiratory Ratio'][i]) + ', '
        wstr += str(data['Breaths per Minute'][i]) + ', '
        wstr += str(data['Maximum Expiratory Time'][i]) + ', '
        wstr += str(data['Inspiratory Time'][i]) + ', '
        wstr += str(data['Pressure Threshold'][i])
        f.write(wstr)

    f.close()
    return "temp.csv"


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              [Input('interval-component', 'n_intervals'),
              Input('xaxis-dropdown', 'value')])
def update_graph_live(n, secs):
    # Create the graph with subplots
    fig = plotly.subplots.make_subplots(rows=3, cols=2, vertical_spacing=0.2,
    subplot_titles = ('Inspiratory Flow Rate (SLPM)', 'Expiratory Flow Rate (SLPM)',
    'Inspiratory Pressure (cmH20)', 'Expiratory Pressure (cmH20)',
    'Inspiratory Tidal Volume (L)', 'Expiratory Tidal Volume (L)'))
    fig['layout']['margin'] = {
        'l': 10, 'r': 10, 'b': 5, 't': 40
    }
    fig.update_layout(showlegend=False) # titles make legend redundant

    fig.append_trace({
        'x': data['Time'],
        'y': data['Inspiratory Flow Rate'],
        'name': 'Flow Rate',
        'mode': 'lines',
        'type': 'scatter'
    }, 1, 1)
    fig.append_trace({
        'x': data['Time'],
        'y': data['Inspiratory Pressure'],
        'name': 'Pressure',
        'mode': 'lines',
        'type': 'scatter'
    }, 2, 1)
    fig.append_trace({
        'x': data['Time'],
        'y': data['Inspiratory Tidal Volume'],
        'name': 'Volume',
        'mode': 'lines',
        'type': 'scatter'
    }, 3, 1)
    fig.append_trace({
        'x': data['Time'],
        'y': data['Expiratory Flow Rate'],
        'name': 'Flow Rate',
        'mode': 'lines',
        'type': 'scatter'
    }, 1, 2)
    fig.append_trace({
        'x': data['Time'],
        'y': data['Expiratory Pressure'],
        'name': 'Pressure',
        'mode': 'lines',
        'type': 'scatter'
    }, 2, 2)
    fig.append_trace({
        'x': data['Time'],
        'y': data['Expiratory Tidal Volume'],
        'name': 'Volume',
        'mode': 'lines',
        'type': 'scatter'
    }, 3, 2)

    fig.update_xaxes(range=[datetime.datetime.now()-datetime.timedelta(seconds=secs), datetime.datetime.now()])

    #print(app.data['Flow Rate'].tolist())
    return fig


@app.callback(Output('download-link', 'href'),
              [Input('interval-component', 'n_intervals')])
def update_href(dropdown_value):
    timestr = time.strftime("%Y%m%d-%H%M%S") # make time based filename
    relative_filename = os.path.join(
        'download',
        'gVent' + timestr + '.csv')
    return '/{}'.format(relative_filename)


@app.server.route('/download/<path:path>')
def serve_static(path):
    return flask.send_from_directory(
        os.getcwd(), make_csv()
    )

if __name__ == '__main__':
    app.run_server(debug=True)
