import datetime

import dash
import pandas
import dash_core_components as dcc
import dash_html_components as html
import plotly
from dash.dependencies import Input, Output
from sens_sim import fake_sim


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

data = {
    'time': [],
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
            html.H3('Flow Rate'),
            html.Span('{0:.2f}'.format(flow_rate), style=style)
        ], className="four columns"),
        html.Div([
            html.H3('Pressure'),
            html.Span('{0:.2f}'.format(pressure), style=style)
        ], className="four columns"),
        html.Div([
            html.H3('Volume'),
            html.Span('{0:0.2f}'.format(volume), style=style)
        ], className="four columns")
    ]
    """
    return [
        html.Span('Flow Rate: {0:.2f}'.format(flow_rate), style=style),
        html.Span('Pressure: {0:.2f}'.format(pressure), style=style),
        html.Span('Volume: {0:0.2f}'.format(volume), style=style)
    ]"""


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              [Input('interval-component', 'n_intervals')])
def update_graph_live(n):
    # Collect some data

    time = datetime.datetime.now()
    volume = sim.get_vol()
    flow_rate = sim.get_fr()
    pressure = sim.get_pres()
    data['Flow Rate'].append(volume)
    data['Pressure'].append(flow_rate)
    data['Volume'].append(pressure)
    data['time'].append(time)

    # Create the graph with subplots
    fig = plotly.subplots.make_subplots(rows=3, cols=1, vertical_spacing=0.2)
    fig['layout']['margin'] = {
        'l': 30, 'r': 10, 'b': 30, 't': 10
    }
    fig['layout']['legend'] = {'x': 0, 'y': 1, 'xanchor': 'left'}

    fig.append_trace({
        'x': data['time'],
        'y': data['Flow Rate'],
        'name': 'Flow Rate',
        'mode': 'lines+markers',
        'type': 'scatter'
    }, 1, 1)
    fig.append_trace({
        'x': data['time'],
        'y': data['Pressure'],
        'name': 'Pressure',
        'mode': 'lines+markers',
        'type': 'scatter'
    }, 2, 1)
    fig.append_trace({
        'x': data['time'],
        'y': data['Volume'],
        'name': 'Volume',
        'mode': 'lines+markers',
        'type': 'scatter'
    }, 3, 1)

    return fig


if __name__ == '__main__':
    app.run_server(debug=True)
