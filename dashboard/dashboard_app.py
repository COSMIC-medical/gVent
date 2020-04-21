import datetime

import dash
import pandas
import dash_core_components as dcc
import dash_html_components as html
import plotly
from dash.dependencies import Input, Output
from sens_sim import fake_sim

font_size   = 80
font_str    = str(font_size) + "px"


external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

sim = fake_sim()

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    html.Div([
        html.H4('UBC SOS eVent Gravity Ventilator Dashboard'),
        html.Div(id='live-update-text', className="row"),
        dcc.Graph(id='live-update-graph'),
        dcc.Interval(
            id='interval-component',
            interval=1*1000, # in milliseconds
            n_intervals=0
        )
    ])
)
app.data = pandas.DataFrame(columns=['Time', 'Flow Rate', 'Pressure', 'Volume'])
data = {
    'Time': [],
    'Flow Rate': [],
    'Pressure': [],
    'Volume': []
}


@app.callback(Output('live-update-text', 'children'),
              [Input('interval-component', 'n_intervals')])
def update_metrics(n):
    volume = sim.get_vol()
    flow_rate = sim.get_fr()
    pressure = sim.get_pres()
    style = {'padding': '5px', 'fontSize': '16px'}
    return [
        html.Div([
            html.H4('Flow Rate'),
            html.Span('{0:.2f}'.format(flow_rate), style={'fontSize': font_str})
        ], className="three columns"),
        html.Div([
            html.H4('Pressure'),
            html.Span('{0:.2f}'.format(pressure), style={'fontSize': font_str})
        ], className="three columns"),
        html.Div([
            html.H4('Volume'),
            html.Span('{0:0.2f}'.format(volume), style={'fontSize': font_str})
        ], className="three columns")
    ]


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_graph_live(n):
    # Collect some data

    time = datetime.datetime.now()
    volume = sim.get_vol()
    flow_rate = sim.get_fr()
    pressure = sim.get_pres()
    new_row = {'Time':[time], 'Flow Rate':[flow_rate], 'Pressure':[pressure], 'Volume':[volume]}
    app.data = app.data.append(new_row, ignore_index=True)

    data['Flow Rate'].append(volume)
    data['Pressure'].append(flow_rate)
    data['Volume'].append(pressure)
    data['Time'].append(time)
    # Create the graph with subplots
    fig = plotly.subplots.make_subplots(rows=3, cols=1, vertical_spacing=0.2)
    fig['layout']['margin'] = {
        'l': 30, 'r': 10, 'b': 30, 't': 10
    }
    fig['layout']['legend'] = {'x': 0, 'y': 1, 'xanchor': 'left'}

    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Flow Rate'][-60:],
        'name': 'Flow Rate',
        'mode': 'lines',
        'type': 'scatter'
    }, 1, 1)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Pressure'][-60:],
        'name': 'Pressure',
        'mode': 'lines',
        'type': 'scatter'
    }, 2, 1)
    fig.append_trace({
        'x': data['Time'][-60:],
        'y': data['Volume'][-60:],
        'name': 'Volume',
        'mode': 'lines',
        'type': 'scatter'
    }, 3, 1)
    #print(app.data['Flow Rate'].tolist())
    return fig



if __name__ == '__main__':
    app.run_server(debug=True)
