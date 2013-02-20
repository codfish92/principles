(require racket/trace);for recursion





;will return true or false stating whether a move is valid or not
;the board is currently in my head going to be a list, where each element is a list containing a number representing the number of sticks left in a stack
(define (isvalid board stack amount)
   (if (or (negative? stack) (negative? amount) (zero? amount) (negative? (- (length board) stack))); if any of the numbers passed in make no sense, just fail
       #f; you gave a value for amount or stack that just doesn't make any sense, like a negative amount of sticks
       (isvalidStep board (- stack 1) amount)
       ); end fail fast if
  );end define

;the recursive part of isvalid, doesn't need to make sure stack will be in the bounds of board because check is done earlier
(define (isvalidStep board stack amount)
  (if (zero? stack) ; check to see if we're refencing the correct stack
      (if (negative? (- (caar board) amount)) ; check to see amount is equal to or less than amount in stack
          #f ; your trying to pull too many sticks out of stack
          #t ; its a valid move
          )
      (isvalidStep (cdr board) (- stack 1) amount) ; keep going until you start to refrence correct stack
      )
  );end define




;to make random number use (random k) where it will generate ints from 1 to k-1. 
;the randomComp will use the (random k) function to pick both a stack to take from, and the amount to take
(define (random)
  #f
  );end define








;printStack will assume a non zero number is passed into it, and will do a check to make sure it does not do a recurisive call on a zero
(define (printStack sticks)
  (display (string-append (make-string 1 #\X) " "))
  (if (equal? 1 (- sticks 1))
      (display "X:") ;return a X:
      (printStack (- sticks 1)); run printStack with 
      );end if
  );end define

;assumes proper format
(define (printBoardStep board)
  (if (empty? board)
      (display ";;;;;;;;;;\n")
      (begin (printStack (caar board)) (display "\n") (printBoardStep (cdr board)))
      
      );end if
  );end define

; output board
(define (printBoard board)
  (display ";;;;;;;;;;\n")
  (printBoardStep board)
  ); end define



(define testBoard '[(3) (5) (7) (2)]) ; for testing
(define players '(0 1));0 is human 1 is random 2 is smart
;(trace printBoardStep)