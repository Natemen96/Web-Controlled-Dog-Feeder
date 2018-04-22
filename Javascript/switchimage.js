var txtFile = new XMLHttpRequest();
//console.log('UNSENT', txtFile.readyState); // readyState will be 0
txtFile.open("GET", "../HTML/Images/Bowl.txt", true);
//console.log('OPENED', txtFile.readyState); // readyState will be 1
//console.log('TEST', txtFile.status); // readyState will be 1


a = 5;
txtFile.onreadystatechange = function() {
	if (txtFile.readyState === 4) {
		//console.log(a);
    var status = txtFile.status;
    if ((status >= 200 && status < 300) || status === 304) {
      //console.log(txtFile.responseText);
		  allText = txtFile.responseText;
  	  lines = txtFile.responseText.split("\n"); // Will separate each line into an array
		  document.getElementById('myImage').src="../HTML/Images/"+lines[0];
		  //console.log(lines[0]);
    } else {
      alert("Broke");
    }
}
};
txtFile.send(null);
//alert(txtFile.responseText)
//console.log('DONE', txtFile.readyState); // readyState will be 4
