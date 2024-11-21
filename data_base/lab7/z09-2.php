<html>
	<head><title>Fill table</title></head>
	<body>
		<?php
			function addToDataBase($_name, $_city, $_address, $_birthday, $_mail, &$db_error){
				try{
					$conn=mysqli_connect("localhost","root","");
					mysqli_select_db($conn,"sample");
					$query="INSERT INTO notebook_br4 (name, city, address, birthday, mail) VALUES ('$_name', '$_city', '$_address', '$_birthday', '$_mail');";
					mysqli_query($conn,$query);
					mysqli_close($conn);
				}
				catch(mysqli_sql_exception $exp){
					$db_error=$exp->getMessage();
					return false;
				}
				return true;
			}

			function writeForm(){
				print "<form action='{$_SERVER['PHP_SELF']}' method='post'>";
				print "<p>Имя:</p>";
				print "<input type='text' name='i_name'> ";
				print "<p>Город:</p>";
				print "<input type='text' name='i_city'> ";
				print "<p>Адрес:</p>";
				print "<input type='text' name='i_address'> ";
				print "<p>День рождения:</p>";
				//print "<input type='date' name='i_birthday' value='2024-10-01'> ";
				print "<input type='text' name='i_birthday'> ";
				print "<p>Почта:</p>";
				print "<input type='text' name='i_mail'> ";
				print "<p><input type='submit' value='Добавить запись'/></form>";
			}

			if((isset($_POST['i_name']) && $_POST['i_name']!="") && (isset($_POST['i_mail']) && $_POST['i_mail']!="")){
				$db_error="";
				$ret=addToDataBase($_POST['i_name'],$_POST['i_city'],$_POST['i_address'],$_POST['i_birthday'],$_POST['i_mail'],$db_error);
				if(!$ret) print "Ошибка: $db_error";
			}
			writeForm();

			print "<a href='z09-1.php'>Создать новую таблицу<br></a>";
			print "<a href='z09-3.php'>Просмотреть таблицу</a>";
		?>
	</body>
</html>