|| File: testtop.m
|| Top level test of Miranda support library.
%include "test.m"

(dt,rem) = scanlist scan_plot (read "testdata")
testit = (showlist show_plot dt)

allchars = [decode n | n<-[0..255]]
genstr = show_plot (TestString allchars)
genchars = showlist show_plot [TestChar c | c <- allchars]
forcecompile = "This is a dummy to force compilation"
