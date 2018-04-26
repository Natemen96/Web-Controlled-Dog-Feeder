//switchimage code
var txtFile = new XMLHttpRequest();

txtFile.open("GET", "../HTML/Images/Bowl.txt", true);


a = 5;
txtFile.onreadystatechange = function() {
	if (txtFile.readyState === 4) {

    var status = txtFile.status;
    if ((status >= 200 && status < 300) || status === 304) {

		  allText = txtFile.responseText;
  	  lines = txtFile.responseText.split("\n");
		  document.getElementById('myImage').src="../HTML/Images/"+lines[0];
    } else {
      alert("Broke");
    }
}
};
txtFile.send(null);
