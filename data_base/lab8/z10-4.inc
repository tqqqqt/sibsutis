<?php
	try{
		$conn=mysqli_connect("localhost","root","");
		mysqli_select_db($conn,"sample");
	}
	catch(mysqli_sql_exception $exp){
		die("Error: ".$exp);
	}
?>