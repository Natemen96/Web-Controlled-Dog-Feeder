var chart1, chart2;

(function chartOne() {
  var dps = [ { y: 90 }, { y: 100 } ], // dataPoints
    yVal = 100,
    updateInterval = 300;

  chart1 = new CanvasJS.Chart("chart1Container", {
    title: {
      text: "Chart 1 - Live Random Data"
    },
    data: [{
      type: "line",
      dataPoints: dps
    }]
  });
  chart1.render();

  var updateChart1 = function(count) {
    count = count || 1; // count is number of times loop runs to generate random dataPoints.

    for (var j = 0; j < count; j++) {
      yVal = yVal + Math.round(5 + Math.random() * (-5 - 5)); //assign y-value here
      dps.push({
        y: yVal
      });
    };
    chart1.render();
  };

  // update chart after specified time.
  setInterval(function() {
    updateChart1()
  }, updateInterval); //Remove setInterval and call updateChart when y-vlaue is available
})();

function chartTwo() {
  var dps = [ { y: 90 }, { y: 100 } ], // dataPoints
    yVal = 100,
    updateInterval = 800;

  chart2 = new CanvasJS.Chart("chart2Container", {
    title: {
      text: "Chart 2 - Live Random Data"
    },
    data: [{
      type: "line",
      color: "#c24642",
      dataPoints: dps
    }]
  });
  chart2.render();

  var updateChart2 = function(count) {
    count = count || 1; // count is number of times loop runs to generate random dataPoints.
    for (var j = 0; j < count; j++) {
      yVal = yVal + Math.round(5 + Math.random() * (-5 - 5)); //assign y-value here
      dps.push({
        y: yVal
      });
    };
    chart2.render();
  };

  // update chart after specified time.
  setInterval(function() {
    updateChart2()
  }, updateInterval); //Remove setInterval and call updateChart when y-vlaue is available
}

$('#bs-tab2').on("shown.bs.tab", function() {
  chartTwo();
  $('#bs-tab2').off(); // to remove the binded event after the initial rendering
  renderChartEvents();
});

function renderChartEvents() {
  $('#bs-tab1').on("shown.bs.tab", function() {
    chart1.render();
  });
  $('#bs-tab2').on("shown.bs.tab", function() {
    chart2.render();
  });
}
