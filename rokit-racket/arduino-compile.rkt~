#lang racket

(provide send-to-arduino)

(require racket-to/processing)



(define (send-to-arduino code)
  (define compiled-s
    (string-append
     "#include <SmartInventor.h>\n\n" ;Figure imports out automatically based on code??
     (processing-str code)))

  (displayln compiled-s)

  (make-directory* "demo")
  (with-output-to-file "demo/demo.ino" #:exists 'replace
    (lambda () (printf compiled-s)))

  ;TODO: Make this cross platform!!!
  (system "cp -r rokitarduinov1-0-9/* demo/")

  ;This too!!!
  (system "/Applications/Arduino.app/Contents/MacOS/Arduino --upload --preferences-file ./rokitprefs.txt ./demo/demo.ino"))



 