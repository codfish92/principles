(require racket/trace) ; used for (trace funcName)
(define aSampleList (list 'a 'b 'c 'd)); a test list
(define anotherSampleList (list 'b 'c (list 'a 'b 'c))) ; a more complicated test list using a list inside of a list
;part 1
;containsAnywhere works by car'ing the list to see if the first element is the element you want, otherwise it will call containsAnywhere recursivly with the cdr of the list. you cant car an empty list so an empty list check is done first
; if you have to check an empty list, clearly the element was never in there.
(define (containsAnywhere element aList) ; given an element and a valid list
  (if (empty? aList) ; if the list is empty
      #f;return false
      (if (list? (car aList))
          (containsAnywhere element (car aList))
          (if (equal? element (car aList)) ; else if the first element of the list is the element were looking for
              #t ; return true
              (containsAnywhere element (cdr aList)))))); other wise send the list (minus the first element) to the function contains anywhere



;part 2
;the function that handels the recursion of removeAll
(define (removeAllStep element aList returnList)
  (if (empty? aList) ;if the list is empty
      returnList; return the returnList
      (if (list? (car aList))
          (removeAllStep element (cdr aList) (append returnList (list (removeAll element (car aList))))) ; if the first element in aList is a list in self, it will append the result of that list going through the removeall function to the returnlist as it goes through the remove all step again
          (if (not (equal? element (car aList))) ; if the elementInQuestion is not the element we want to remove
          (removeAllStep element (cdr aList) (append returnList (list (car aList)))) ; add it to the returnList
          (removeAllStep element (cdr aList) returnList) ; just recurse without the append
          ); end if not equal     
       );end check for list
  );end if empty list
);end define


;removeAll will work by car'ing the list and seeing if it is the element you want to remove. if it is, it will simply call cdr on the rest of the list, otherwise it will append the element returned from car into another list. 
;returns the second list after an empty list is encountered
(define (removeAll element aList) ;given an element and a valid list
  (define returnList (list)) ; this list will contain the elements 
  (if (containsAnywhere element aList) ;if the element your looking to remove is in the list
      (removeAllStep element aList returnList) ; remove all elements of it
      aList ; just print out the orginal list
  ); end if containsAnywhere
 )


;part 3
;converts x feet to meters
(define (feet-to-meters x)
  (/ x 3.2808) ; m = f/3.2808
  );end define

;converts x meters to feet
(define (meters-to-feet x)
  (* x 3.2808) ; f = m * 3.2808
  );end define

;converts x fahrenheit to celcius
(define (fahrenheit-to-celcius x)
  (* (/ 5 9) (- x 32)) ; c = (f-32) * 5/9
  );end define

;converts x celcius to fahrenheit
(define (celcius-to-fahrenheit x)
  (+ (* x (/ 9 5)) 32) ; f = c * 9/5 +32
  );end define



(define (conversionCalculator)
  (display "Enter the unit you want to convert: ")
  (define unit1 (read)); read in the first input
  (display "\nEnter the unit you want to convert to: ")
  (define unit2 (read)); read int the second input
  (display "\nEnter the number of unit 1 you have: ")
  (define num (read))
  (define funcName (string->symbol (string-append (symbol->string unit1) (string-append "-to-" (symbol->string unit2)))))
  (display funcName)
  (display (symbol? funcName))
  ((eval funcName) num);run the function found
  ) ;end define

(conversionCalculator)
