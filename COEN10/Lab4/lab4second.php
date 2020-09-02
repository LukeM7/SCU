<html>
	<body>
		<H1> How'd You Fare? </H1>
			<?php
				$num1 = $_POST["num1"];
				$num2 = $_POST["num2"];
				$num3 = $_POST["num3"];
				$num4 = $_POST["num4"];
				$num5 = $_POST["num5"];

				$counter = 0;
				$num=array ($num1, $num2, $num3, $num4, $num5);

				$rand=array (0,0,0,0,0);
				for ($i=0;$i<5;$i++)
				{
						$rand[$i]=rand(0,20);
						if ($i != 0)
						{
							for ($j=0;$j<$i;$j++)
								if ($rand[$i]==$rand[$j])
								{
									$i--;
									break;
								}
						}
				}
									/* This loop is to make sure each random number in the array is unique */					
				echo "The numbers: ", $rand[0], " ", $rand[1], " ", $rand[2], " ", $rand[3], " ", $rand[4];
				echo "Your numbers: ", $num1, " ", $num2, " ", $num3, " ", $num4, " ", $num5;
			?>
			<?php
				for ($i=0; $i<5; $i++)
					for ($j=0; $j<5; $j++)
						if ($num[$j]==$rand[$i])
							$counter++;
					if ($counter>=1)
						echo "You got ", $counter, " right!";
					else
						echo "Wrong!";	
				/* This loop is to count how many of the numbers in each array match and output that value in the results */
			?>
			
			<form method="POST" action="lab4main.php">
				<input type="submit" value="Try Again!" />
			</form>
	</body>
</html>
