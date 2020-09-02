

object problem3 extends App{
  def apply_combine2(f:Int => Int): Int => (((Int,Int) => Int) => Int) = { // Can take in a function that takes in an Int and returns an Int
    def combine(x:Int): ((Int,Int) => Int) => Int = { // Takes in an Int and returns a function that takes in a function 
      def combineAgain(g:(Int,Int) => Int): Int = { // Takes in a function that takes two Ints and returns an Int and then returns an Int
        if(x==1) f(1)
        else g(f(x),combine(x-1)(g)) // Curry combine with (g)
      }
      combineAgain
    }    
    combine
  }
  
  def apply_square = apply_combine2((x)=>x*x)

  def apply_square_5 = apply_square(5)

  println(apply_combine2((x)=>x*x)(5)((x, y)=>x*y))
  
}