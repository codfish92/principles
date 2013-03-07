#lang racket
;callaborated with Aakash shah, Maria deslis, Anastesa, Miki

(require racket/function)
(require racket/string)
(define articles '(
     ((Test-Driven Learning: Intrinsic Integration of Testing into the CS/SE Curriculum)
      ((David Jansen)(Hossein Saiedian))
      ("Test-driven learning" "test-driven development" "extreme programming" "pedagogy" "CS1"))
     ((Process Improvement of Peer Code Review and Behavior Analysis of its Participants)
      ((WANG Yan-qing) (LI Yi-jun) (Michael Collins) (LIU Pei-jie))
      ("peer code review" "behavior analysis" "software quality assurance" 
        "computer science education" "software engineering"))
     ((Computer Games as Motivation for Design Patterns)
      ((Paul V. Gestwicki))
      ("Design Patterns" "Games" "Pedagogy" "Java"))
     ((Killer "Killer Examples" for Design Patterns)
      ((Carl Alphonce) (Michael Caspersen) (Adrienne Decker))
      ("Object-orientation" "Design Patterns"))
     ((Test-First Java Concurrency for the Classroom)
      ((Mathias Ricken)(Robert Cartwright))
      ("CS education" "Java" "JUnit" "unit testing" "concurrent programming"
       "tools" "software engineering"))
     ((Teaching Design Patterns in CS1: a Closed Laboratory Sequence
                based on the Game of Life)
      ((Michael Wick))
      ("Design Patterns" "Game of Life" "CS1" "Laboratory"))
   ))

(define (getTitle article)
  (if (empty? article)
      (display "not an article")
      (car article)
      );end if
  );end define

(define (getAuthors articles)
  (if (empty? articles)
      (display "not an article")
      (second articles)
      );end if
  );end define

(define (getKeyword article)
  (if (empty? article)
      (display "not an article")
      (third article)
      )
  );end define
;   
;(define (createSearch keyword)
 ; (lambda (x) (x keyword))
 ; );end define

;(define (isInString x keywords)
 ; (if (empty? keywords)
 ;     #t
 ;     #f
 ;     );end if
 ; );end define

;communicated heavily with the collabartes up at the top of the page

(define (keywordSearch keyword articles)
  (map getTitle ( searchFunction (makeSearch keyword) articles)); apply getTitle to all matched articles from the doSearch function
  );end define

(define (makeSearch keyword)
  (curry doSearch keyword); curry the keyword up so foldl can use it with 
  );end define

(define (searchFunction searchCurried articles) ;the curried function should be applied to all articles
  (foldl searchCurried '() articles); use foldl with an empty list as the start state and articles on what to iterate over
  );end define

(define (doSearch keyword currentArticle matchedArticles)
  (if (member keyword (getKeyword currentArticle)); if the keyword is in the the keywords?
      (append matchedArticles (list currentArticle)); add the article to the list of matched articles
      matchedArticles;otherwise just return the current matched articles
      );end if
  );end define 
(keywordSearch "Java" articles)
  
;(define titleList '())
;(define (old-keywordSearch keyword article titles)
;  (if (empty? article)
 ;     titles
  ;    (if (list? (memq keyword (getKeyword (car article))))
  ;        (keywordSearch keyword (cdr article) (append titles (getTitle (car article))))
  ;        (keywordSearch keyword (cdr article) titles)
  ;        );end if
  ;    );end if
  ;);end define
;(string-ci=)
