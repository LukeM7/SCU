<html>
<body>

<H1> Manzitto's Multiplication Table </H1>

<?php

	$num1 = $_POST["num1"];
	$num2 = $_POST["num2"];
	$num3 = $_POST["num3"];

	echo $num1;
	echo "x";
	echo $num2;
	echo "=";
	echo $num1*$num2;

	if($num3==$num1*$num2)
		 echo "Good Job!";
	else
		echo "You need practice";
?>
	

<form method="POST" action="lab2main.php">
	<input type="submit" value="Try again" />
</form>

</body>
</html>

