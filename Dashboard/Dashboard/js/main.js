$(document).ready(function () {
    LoadHighcharts();
    GetOBDReadings();
});

function GetOBDReadings() {
	var soapRequest =
	'<?xml version="1.0" encoding="UTF-8"?> \
	<SOAP-ENV:Envelope \
	xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/" \
	xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/" \
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" \
	xmlns:xsd="http://www.w3.org/2001/XMLSchema" \
	xmlns:OBD="http://tempuri.org/OBD.xsd"> \
	<SOAP-ENV:Body> \
	<OBD:GetReadings> \
	</OBD:GetReadings> \
	</SOAP-ENV:Body> \
	</SOAP-ENV:Envelope>';
    
	$.ajax({
        url: "http://192.168.1.3:2014/",
        type: "POST",
		data: soapRequest,
        success: HandleReceivedReadings,
        error: AlertError,
        complete: function() {
            setTimeout(GetOBDReadings, 1000);
        }
    });
}

function AlertError(data, status, req) {
    RandomData();
}

function RandomData() {
    var rand = Math.floor((Math.random() * 50 + 1));
    var element = document.getElementById("speed-value");
    element.innerHTML = rand;
    var point = Highcharts.charts[0].series[0].points[0];
    point.update(rand);
    point = Highcharts.charts[0].series[0].points[1];
    point.update(200 - rand);
    var shift = Highcharts.charts[1].series[0].data.length > 20;
    Highcharts.charts[1].series[0].addPoint(rand, true, shift);

    rand = Math.floor((Math.random() * 5000 + 1));
    element = document.getElementById("revolution-value");
    element.innerHTML = rand;
    point = Highcharts.charts[2].series[0].points[0];
    point.update(rand);
    point = Highcharts.charts[2].series[0].points[1];
    point.update(5000 - rand);
    shift = Highcharts.charts[3].series[0].data.length > 20;
    Highcharts.charts[3].series[0].addPoint(rand, true, shift);
}

function HandleReceivedReadings(data, status, req) {
    var speed = $(req.responseXML).find("speed");
    //var revolution = $(req.responseXML).find("speed");
    var revolution = $(req.responseXML).find("revolution");

	var element = document.getElementById("speed-value");
    element.innerHTML = speed[0].innerHTML;
    var point = Highcharts.charts[0].series[0].points[0];
    point.update(parseInt(speed[0].innerHTML));
    point = Highcharts.charts[0].series[0].points[1];
    point.update(200 - parseInt(speed[0].innerHTML));
    var shift = Highcharts.charts[1].series[0].data.length > 20;
    Highcharts.charts[1].series[0].addPoint(parseInt(speed[0].innerHTML), true, shift);

    element = document.getElementById("revolution-value");
    element.innerHTML = revolution[0].innerHTML;
    point = Highcharts.charts[2].series[0].points[0];
    point.update(parseInt(revolution[0].innerHTML));
    point = Highcharts.charts[2].series[0].points[1];
    point.update(5000 - revolution[0].innerHTML);
    shift = Highcharts.charts[3].series[0].data.length > 20;
    Highcharts.charts[3].series[0].addPoint(parseInt(revolution[0].innerHTML), true, shift);
}

function LoadHighcharts() {
    SpeedPieChart();
    SpeedLineChart();
    RevolutionPieChart();
    RevolutionLineChart();
}

function SpeedPieChart() {
    $(function () {
        $('#speed-pie-chart').highcharts({
            chart: {
                plotBackgroundColor: null,
                plotBorderWidth: 0,
                plotShadow: false,
                backgroundColor: null,
                spacing: 0,
            },
            colors: [
                '#FFFFFF',
                '#b8ee83'
            ],
            title: {
                text: ''
            },
            credits: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            plotOptions: {
                pie: {
                    dataLabels: {
                        enabled: false,
                        distance: -50,
                        style: {
                            fontWeight: 'bold',
                            color: 'white',
                            textShadow: '0px 1px 2px black'
                        }
                    },
                    startAngle: -120,
                    endAngle: 120,
                    center: ['50%', '28%'],
                    borderColor: null
                }
            },
            series: [{
                type: 'pie',
                innerSize: '85%',
                data: [
                    [150],
                    [200 - 150]
                ]

            }]
        });
    });
}

function RevolutionPieChart() {
    $(function () {
        $('#revolution-pie-chart').highcharts({
            chart: {
                plotBackgroundColor: null,
                plotBorderWidth: 0,
                plotShadow: false,
                backgroundColor: null,
                spacing: 0,
            },
            colors: [
                '#FFFFFF',
                '#b5ebff'
            ],
            title: {
                text: ''
            },
            credits: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            plotOptions: {
                pie: {
                    dataLabels: {
                        enabled: false,
                        distance: -50,
                        style: {
                            fontWeight: 'bold',
                            color: 'white',
                            textShadow: '0px 1px 2px black'
                        }
                    },
                    startAngle: -120,
                    endAngle: 120,
                    center: ['50%', '28%'],
                    borderColor: null
                }
            },
            series: [{
                type: 'pie',
                innerSize: '85%',
                data: [
                    [150],
                    [200 - 150]
                ]

            }]
        });
    });
}

function SpeedLineChart() {
    $(function () {
        $('#speed-graph-chart').highcharts({
            chart: {
                backgroundColor: null,
                width: 510,
                height: 250,
                margin: 15
            },
            title: {
                text: ''
            },
            subtitle: {
                text: ''
            },
            legend: {
                enabled: false
            },
            credits: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            colors: [
                '#FFFFFF'
            ],
            plotOptions: {
                line: {
                    lineWidth: 4,
                    enableMouseTracking: true
                }
            },
            xAxis: {
                categories: [],
                lineWidth: 0,
                tickmarkPlacement: 'on',
                labels: {
                    enabled: false,
                },
            },
            yAxis: [{
                max: 200,
                min: 0,
                gridLineWidth: 0,
                title: {
                    text: ''
                },
                labels: {
                    enabled: false
                },
                plotLines: [{
                    value: 0,
                    width: 3,
                    color: '#FFFFFF'
                },
                {
                    value: 10,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 20,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 30,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 40,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 50,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 60,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 70,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 80,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 90,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 100,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 110,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 120,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 130,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 140,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 150,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 160,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 170,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 180,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 190,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 200,
                    width: 2,
                    color: '#FFFFFF'
                }]
            }],
            tooltip: {
                valueSuffix: ' km/h'
            },
            series: [{
                name: 'Speed',
                data: [0]
            }]
        });
    });
}

function RevolutionLineChart() {
    $(function () {
        $('#revolution-graph-chart').highcharts({
            chart: {
                backgroundColor: null,
                width: 510,
                height: 250,
                margin: 15
            },
            title: {
                text: ''
            },
            subtitle: {
                text: ''
            },
            legend: {
                enabled: false
            },
            credits: {
                enabled: false
            },
            exporting: {
                enabled: false
            },
            colors: [
                '#FFFFFF'
            ],
            plotOptions: {
                line: {
                    lineWidth: 4,
                    enableMouseTracking: true
                }
            },
            xAxis: {
                categories: [],
                lineWidth: 0,
                tickmarkPlacement: 'on',
                labels: {
                    enabled: false,
                },
            },
            yAxis: [{
                max: 5000,
                min: 0,
                gridLineWidth: 0,
                title: {
                    text: ''
                },
                labels: {
                    enabled: false
                },
                plotLines: [{
                    value: 0,
                    width: 3,
                    color: '#FFFFFF'
                },
                {
                    value: 500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 1000,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 1500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 2000,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 2500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 3000,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 3500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 4000,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 4500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 5000,
                    width: 2,
                    color: '#FFFFFF'
                },
                {
                    value: 5500,
                    width: 1,
                    color: '#FFFFFF'
                },
                {
                    value: 6000,
                    width: 2,
                    color: '#FFFFFF'
                }]
            }],
            tooltip: {
                valueSuffix: ' RPM'
            },
            series: [{
                name: 'Revolution',
                data: [0]
            }]
        });
    });
}