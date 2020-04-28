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

sim = fake_sim('baba')

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    html.Div([
        html.H2('gVent Monitoring Dashboard'),
        html.Div(id='live-update-text', className="row"),
        dcc.Graph(id='live-update-graph'),
        dcc.Interval(
            id='interval-component',
            interval=1*1000, # in milliseconds
            n_intervals=0
        ),
        html.A(id='download-link', children='Download File'),
    ])
)

app.f = open('temp.csv', 'w')
app.f.write("Time,\
Inspiratory Pressure,\
Expiratory Pressure,\
Inspiratory Flow Rate,\
Expiratory Flow Rate,\
Inspiratory Tidal Volume,\
Expiratory Tidal Volume")

data = {
    'Time': [],
    'Inspiratory Flow Rate': [],
    'Expiratory Flow Rate': [],
    'Inspiratory Pressure': [],
    'Expiratory Pressure': [],
    'Inspiratory Tidal Volume': [],
    'Expiratory Tidal Volume': []
}


@app.callback(Output('live-update-text', 'children'),
              [Input('interval-component', 'n_intervals')])
def update_metrics(n):
    sensor_data = sim.readline()
    sensor_words = sensor_data.split(', ')

    ins_pres    = float(sensor_words[0])
    ex_pres     = float(sensor_words[1])
    ins_fr      = float(sensor_words[2])
    ex_fr       = float(sensor_words[3])
    ins_vol     = float(sensor_words[4])
    ex_vol      = float(sensor_words[5])

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


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_graph_live(n):
    # Collect some data

    time = datetime.datetime.now()
    sensor_data = sim.readline()
    app.f.write("\n" + time.strftime("%d-%b-%Y %H:%M:%S.%f") + ', ' + sensor_data)
    sensor_words = sensor_data.split(', ')

    ins_pres    = float(sensor_words[0])
    ex_pres     = float(sensor_words[1])
    ins_fr      = float(sensor_words[2])
    ex_fr       = float(sensor_words[3])
    ins_vol     = float(sensor_words[4])
    ex_vol      = float(sensor_words[5])
    #new_row = {'Time':[time], 'Flow Rate':[flow_rate], 'Pressure':[pressure], 'Volume':[volume]}
    #app.data = app.data.append(new_row, ignore_index=True)

    data['Time'].append(time)

    data['Inspiratory Flow Rate'].append(ins_fr)
    data['Inspiratory Pressure'].append(ins_pres)
    data['Inspiratory Tidal Volume'].append(ins_vol)

    data['Expiratory Flow Rate'].append(ex_fr)
    data['Expiratory Pressure'].append(ex_pres)
    data['Expiratory Tidal Volume'].append(ex_vol)

    # Create the graph with subplots
    fig = plotly.subplots.make_subplots(rows=3, cols=2, vertical_spacing=0.2,
    subplot_titles = ('Inspiratory Flow Rate (SLPM)', 'Expiratory Flow Rate (SLPM)',
    'Inspiratory Pressure (cmH20)', 'Expiratory Pressure (cmH20)',
    'Inspiratory Tidal Volume (L)', 'Expiratory Tidal Volume (L)'))
    fig['layout']['margin'] = {
        'l': 30, 'r': 10, 'b': 10, 't': 40
    }
    fig.update_layout(showlegend=False) # titles make legend redundant

    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Inspiratory Flow Rate'][-60:],
        'name': 'Flow Rate',
        'mode': 'lines',
        'type': 'scatter'
    }, 1, 1)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Inspiratory Pressure'][-60:],
        'name': 'Pressure',
        'mode': 'lines',
        'type': 'scatter'
    }, 2, 1)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Inspiratory Tidal Volume'][-60:],
        'name': 'Volume',
        'mode': 'lines',
        'type': 'scatter'
    }, 3, 1)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Expiratory Flow Rate'][-60:],
        'name': 'Flow Rate',
        'mode': 'lines',
        'type': 'scatter'
    }, 1, 2)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Expiratory Pressure'][-60:],
        'name': 'Pressure',
        'mode': 'lines',
        'type': 'scatter'
    }, 2, 2)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Expiratory Tidal Volume'][-60:],
        'name': 'Volume',
        'mode': 'lines',
        'type': 'scatter'
    }, 3, 2)
    #print(app.data['Flow Rate'].tolist())
    return fig


@app.callback(Output('download-link', 'href'),
              [Input('interval-component', 'n_intervals')])
def update_href(dropdown_value):
    timestr = time.strftime("%Y%m%d-%H%M%S")
    relative_filename = os.path.join(
        'download',
        'gVent' + timestr + '.csv')
    absolute_filename = os.path.join(os.getcwd(), relative_filename)

    fname = app.f.name
    app.f.close()

    os.rename(fname, absolute_filename)

    app.f = open(absolute_filename, 'a')

    return '/{}'.format(relative_filename)


@app.server.route('/download/<path:path>')
def serve_static(path):
    root_dir = os.getcwd()
    return flask.send_from_directory(
        os.path.join(root_dir, 'download'), path
    )

if __name__ == '__main__':
    app.run_server(debug=True)
