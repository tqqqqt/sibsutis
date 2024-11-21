<?php
	try{
		$conn=mysqli_connect("localhost","root","");
		mysqli_select_db($conn,"kw");
	}
	catch(mysqli_sql_exception $exp){
		die("Error: ".$exp);
	}
?>