

object problem2 extends App{
  def correspondance(x:List[Int],y:List[Int],f:(Int,Int) => Int): List[Int] = {
    if (x.isEmpty || y.isEmpty) Nil // returns Nil if there isn't a variable in either array to do f
    else f(x.head,y.head)::correspondance(x.tail,y.tail,f) // Add's the value of f to head and then recursively goes through the tail with f
  }
  val x = List(3,51,1,12)
  val y = List(6,43,65,76,23)
  println(correspondance(x,y,(x,y)=> x+y))
  println(correspondance(x,y,(x,y) => x*x+y))
}