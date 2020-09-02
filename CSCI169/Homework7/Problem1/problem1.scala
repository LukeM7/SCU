

object problem1 extends App{
  def integrate(x: List[Int],y: List[Int]) : List[Int] = {
    if (x.isEmpty) y // If the x array is empty then fill the rest with y's values
    else if (y.isEmpty) x // If the y array is empty then fill the rest with x values
    else x.head::integrate(y,x.tail) // By calling y in the x and vice versa the alternating elements is achieved
  }
  
  val x = List(1,3,5,7)
  val y = List(2,4,6,8,9,10)
  println(integrate(x,y))
}