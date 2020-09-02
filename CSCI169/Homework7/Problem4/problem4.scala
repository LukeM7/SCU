

object problem4 extends App{
  def test(f:Int => Boolean): List[Int] => List[Int] = {
    def listCheck(xs:List[Int]): List[Int] = {
      if (xs.isEmpty) Nil
      else if (f(xs.head)) xs.head::listCheck(xs.tail)
      else listCheck(xs.tail)
    }
    listCheck
  }
  
  val xs = List(3,2,23,43,12,25)
  
  def isEven  = test((x) => x%2==0)
  def evenElements = isEven(xs)
  
  println(test((x) => x%2==0)(xs))
  
  def gt10 = test((x) => x>10)
  def gt10elements = gt10(xs)
  
  println(test((x) => x>10)(xs))
}