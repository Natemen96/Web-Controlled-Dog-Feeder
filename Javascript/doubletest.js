var chart1, chart2;



function getDataPointsFromCSV(csv) {

    var dataPoints = [], csvLines = [], points = [], i;
    csvLines = csv.split(/[\r?\n|\r|\n]+/);

    for (i = 0; i < csvLines.length; i + 1) {
        if (csvLines[i].length > 0) {
            points = csvLines[i].split(",");
            dataPoints.push({
                x: parseFloat(points[0]),
                y: parseFloat(points[1])
            });
        }
    }
    return dataPoints;
}

$.get("test.csv", function chartOne (data) {

        var dataPoints = [];
        var chart1 = new CanvasJS.Chart("chart1Container", {
          title: {
               text: "Dog Bowls Eaten",
          },
          data: [{
               type: "line",
               dataPoints: getDataPointsFromCSV(data)
            }]
         });

          chart1.render();

    }) ();

$.get("test.csv", function chartTwo (data) {
      var dataPoints = [];
       var chart2 = new CanvasJS.Chart("chart2Container", {
         title: {
              text: "Dog Bowls Eaten",
         },
         data: [{
              type: "line",
              dataPoints: getDataPointsFromCSV(data)
           }]
        });

         chart2.render();

   }) ();

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
