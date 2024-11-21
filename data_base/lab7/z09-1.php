<html>
	<head><title>Create table</title></head>
	<body>
		<?php
			try{
				$conn=mysqli_connect("localhost","root","");
				mysqli_query($conn,"CREATE DATABASE IF NOT EXISTS sample;");
				mysqli_select_db($conn,"sample");
				mysqli_query($conn,"DROP TABLE IF EXISTS notebook_br4;");
				$query_create_table="CREATE TABLE notebook_br4 (id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY(id), name VARCHAR(50), city VARCHAR(50), address VARCHAR(50), birthday DATE, mail VARCHAR(20));";
				mysqli_query($conn,$query_create_table);
				mysqli_close($conn);
			}
			catch(mysqli_sql_exception $exp){
				die("Ошибка: ".$exp->getMessage());
			}
			
			echo "<p>Таблица создана</p>";
			echo "<a href='z09-2.php'>Добавить элементы</a>"
		?>
	</body>
</html>