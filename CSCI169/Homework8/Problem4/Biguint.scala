

class Biguint(x:Int) {
  var xs:List[Int]
  def addList(xs:List[Int]) = {
    if (xs.isEmpty) Nil
    else xs.head
  }
}