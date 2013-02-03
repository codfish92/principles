(require racket/trace) ; used for (trace funcName)
(define aSampleList (list 'a 'b 'c 'd)); a test list
(define anotherSampleList (list 'b 'c (list 'a 'b 'c))) ; a more complicated test list using a list inside of a list
(define (containsAnywhere element aList) ; given an element and a valid list
  (if (empty? aList)
      #f
      (if (equal? element (car aList)) #t (containsAnywhere element (cdr aList)))))
(containsAnywhere  (list 'a 'b 'c) anotherSampleList)
(list (list 'a 'b 'c))
anotherSampleList
