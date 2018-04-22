<?php

function testfun()
{
   echo "Your test function on button click is working";
}

if(array_key_exists('Bowl',$_POST)){
   testfun();
}

?>
