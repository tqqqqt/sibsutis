<html>
<head>
	<title></title>
</head>
<body>
	<?php
		function showTable($con, $table_name){
			$result=mysqli_query($con,"select * from $table_name;");
			$num_fields=mysqli_num_fields($result);
			echo "<p>Содержание таблицы $table_name:</p>";
			echo "<table border='1' cellpadding='2'>";
			echo "<tr>";
			for($i=0;$i<$num_fields;$i++){
				$name=mysqli_fetch_field_direct($result,$i)->name;
				echo "<td><p align='center'>$name</p></td>";
			}
			echo "</tr>";
			while($row=mysqli_fetch_row($result)){
				echo "<tr>";
				foreach($row as $elem) echo "<td>$elem</td>";
				echo "</tr>";
			}
			echo "</table>";
		}

		include("connect.inc");

		try{
			if(isset($_GET["table"]) && $_GET["table"]!="") showTable($conn,$_GET["table"]);
			else echo "<p>Нет имени таблицы...</p>";
		}
		catch(mysqli_sql_exception $exp){
			die("Ошибка: ".$exp->getMessage());
		}

		include("close.inc");
	?>
</body>
</html>