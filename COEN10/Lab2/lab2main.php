<html>
<body>

<H1> Manzitto's Multiplication Table </H1>

<?php
	$num1 = rand (0,12);
	$num2 = rand (0,12);
?>

<?php
	echo $num1;
	echo"x";
	echo $num2;
?>


<form action="lab2second.php" method="POST">
	<input type="hidden" name="num1" value=<?php echo $num1; ?> />
	<input type="hidden" name="num2" value=<?php echo $num2; ?> />
	<input type="number" name="num3" />
	<input type="submit" name="submit" value="Calculate!" />
</form>

</body>
</html>
