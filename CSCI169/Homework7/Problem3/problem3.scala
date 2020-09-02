

object problem3 extends App{
  def test(xs:List[Int],f:Int => Boolean): List[Int] = {
    if(xs.isEmpty) Nil
    else if (f(xs.head)) xs.head::test(xs.tail,f) // f returns a boolean so we can use it as a condition. If true we can add that element to the list
    else test(xs.tail,f) // Else recurse
  }
  
  val x = List(3,2,1,4,5)
  println(test(x,(x) => x%2==0))
  println(test(x,(x) => x>10))
}