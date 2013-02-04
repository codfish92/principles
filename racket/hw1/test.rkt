(require racket/trace) ; used for (trace funcName)
(define aSampleList (list 'a 'b 'c 'd)); a test list
(define anotherSampleList (list 'b 'c (list 'a 'b 'c))) ; a more complicated test list using a list inside of a list

;containsAnywhere works by car'ing the list to see if the first element is the element you want, otherwise it will call containsAnywhere recursivly with the cdr of the list. you cant car an empty list so an empty list check is done first
; if you have to check an empty list, clearly the element was never in there.
(define (containsAnywhere element aList) ; given an element and a valid list
  (if (empty? aList) ; if the list is empty
      #f;return false
      (if (equal? element (car aList)) ; else if the first element of the list is the element were looking for
          #t ; return true
          (containsAnywhere element (cdr aList))))); other wise send the list (minus the first element) to the function contains anywhere

;the function that handels the recursion of removeAll
(define (removeAllStep element aList returnList)
  (if (empty? aList) ;if the list is empty
      (returnList); return the returnList
      '()
      );end if empty list
  (define x (car aList)); else store the element in question in a var to prevent the element being lost from the car action. then 
      
  (if (not (equal? element x)) ; if the elementInQuestion is not the element we want to remove
      (append returnList (list 'x)) ; add it to the returnListi
      '()
      ); end if not equal 
     (removeAllStep element (cdr aList) returnList)
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

(trace removeAllStep)


(removeAll 'c aSampleList)