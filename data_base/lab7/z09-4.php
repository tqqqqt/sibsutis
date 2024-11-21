<html>
	<head><title>Redact field</title></head>
	<body>
		<?php
			function updateField($_id, $_column, $_value, &$_db_error){
				try{
					$conn=mysqli_connect("localhost","root","");
					mysqli_select_db($conn,"sample");
					$query="update notebook_br4 set {$_column}='{$_value}' where id={$_id};";
					mysqli_query($conn,$query);
					mysqli_close($conn);
				}
				catch(mysqli_sql_exception $exp){
					$_db_error=$exp->getMessage();
					return false;
				}
				return true;
			}

			if((isset($_POST['count_all']) && $_POST['count_all']!="") && (isset($_POST['field_name']) && $_POST['field_name']!="")){
				$db_error="";
				for($i=0;$i<$_POST['count_all'];$i++){
					$temp="id".$i;
					if(isset($_POST[$temp])){
						if(!updateField($_POST[$temp],$_POST['field_name'],$_POST['field_value'],$db_error)){
							echo "<p>Ошибка в $i строке: $db_error</p>";
						}
					}
				}
			}
			try{
				$conn=mysqli_connect("localhost","root","");
				mysqli_select_db($conn,"sample");
				$result=mysqli_query($conn,"select * from notebook_br4;");
				$count_fields=mysqli_num_rows($result);
				echo "<form action='{$_SERVER['PHP_SELF']}' method='post'>";
				echo "<p>Таблица:</p>";
				echo "<table border='1' cellpadding='0px'>";
				echo "<tr>";
				echo "<td width='14px' height='15px' size=1>id</td>";
				echo "<td width='14px' height='15px' size=1>Имя</td>";
				echo "<td width='14px' height='15px' size=1>Город</td>";
				echo "<td width='14px' height='15px' size=1>Адрес</td>";
				echo "<td width='14px' height='15px' size=1>Дата рождения</td>";
				echo "<td width='14px' height='15px' size=1>Почта</td>";
				echo "<td width='14px' height='15px' size=1>Нужно изменить</td>";
				echo "</tr>";
				$curent=0;
				while($row=mysqli_fetch_row($result)){
					echo "<tr>";
					foreach($row as $elem) echo "<td width='14px' height='15px' size=1>$elem</td>";	
					echo "<td align='center'><input type=checkbox name='id$curent' value='$row[0]'></td>";
					echo "</tr>";
					$curent++;
				}
				echo "</table>";
				mysqli_close($conn);
				echo "<hr>";
				echo "<select name='field_name'>";
				echo "<option value='name'>Имя</option>";
				echo "<option value='city'>Город</option>";
				echo "<option value='address'>Адрес</option>";
				echo "<option value='birthday'>Дата рождения</option>";
				echo "<option value='mail'>Почта</option>";
				echo "</select>";
				echo "<input type='hidden' name='count_all' value='$count_fields'>";
				echo "<input type='text' name='field_value' value=''>";
				echo "<input type='submit' value='Изменить'>";
				echo "</form>";
			}
			catch(mysqli_sql_exception $exp){
				die("Ошибка: ".$exp->getMessage());
			}
			echo "<a href='z09-2.php'>Добавить элементы</a>";
		?>
	</body>
</html>