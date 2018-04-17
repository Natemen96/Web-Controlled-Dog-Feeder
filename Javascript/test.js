/*
var xhr = new XMLHttpRequest();
xhr.open("GET", "../HTML/Images/Bowl.txt", false);
xhr.send(null);
alert(xhr.responseText);
*/

var xhr = new XMLHttpRequest();
xhr.open("GET", "../HTML/Images/Bowl.txt", true);
xhr.onreadystatechange = function(){
  if (xhr.readyState === 4){
    alert(xhr.responseText);
  }

};
xhr.send(null);
