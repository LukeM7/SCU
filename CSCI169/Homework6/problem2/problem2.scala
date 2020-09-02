object Problem2 extends App{
  def add(x:Int,y:Int) : Int = x+y
  def square(x:Int) : Int = x * x
  def multiply(x:Int,y:Int) : Int = x * y
  
  def combine(f:Int => Int, x:Int, g:(Int,Int) => Int) : Int = {
    if(x==1) f(1)
    else g(f(x),combine(f,x-1,g))
  }
  
  
  println(combine(square,4,add))
  println(combine((x)=>x*x,5,multiply))
}
