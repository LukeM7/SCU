

object problem2 extends App{
  def forLoop(i:Int, check: Int => Boolean, increment: Int => Int)(statement: => Unit): Unit = {
    if(check(i)) {
      statement
      forLoop(increment(i),check,increment)(statement)
    }
  }
  forLoop(0,(x) => x<10, (x) => x+1)(println("Hello World"))
}