<DOCTYPE! html>
 <html>
  <head>
   <title>Data Collector</title>
<style>
   
   div.data {
	position: static;
	height: 200px;
    width: 50%;
    border: 1px solid blue;
	margin-top: 150px;
    margin-bottom: auto;
    margin-right: auto;
    margin-left: 350px;
    background-color: OldLace;
	
}
</style>
 </head>
    <body bgcolor="Olive">
<div class="data">
<?php


 date_default_timezone_set("Asia/Calcutta");
$TimeStamp = "<br><hr><br>At date & Time " . date("d-m-Y H:i:s");
file_put_contents('dataDisplayer.html', $TimeStamp, FILE_APPEND);  


   if( $_POST["vibration"] ) 
   {
   $data = $_POST["vibration"];
   echo "<br><br><hr><center>Current Vibration Reading is: $data </center><hr> <br>";
   }

	  
	
$var = $_POST["vibration"];

$WriteMyPOST=" Vibration Reading is :      $var";

file_put_contents('dataDisplayer.html', $WriteMyPOST, FILE_APPEND);

/* XML start */

$xml="<vibration> $var </vibration>"; // data generated from form, formatted to XML
$fp = fopen('data.xml', 'w');
fwrite($fp, $xml);
fclose($fp);

/* XML close */

?>
<br>
<center><a href="dataDisplayer.html">Click Here to See all Previous data</a><br>
<br><a href="data.xml">Click Here to open XML file</a></center>
</div>
  </body>
 </html>