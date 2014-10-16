#!/usr/local/lib/R

args<-commandArgs(trailingOnly = TRUE)
if(length(args)<1){
    stop("Usage: Rscript fit.r prefix\n")
}
prefix<-args[1]
infile<-paste(prefix,".txt",sep="")
d<-read.table(infile)
s1<-subset(d,d$V3==1)
s2<-subset(d,d$V3==2)
l1<-s1$V2-s1$V1
l2<-s2$V2-s2$V1

outfile<-paste(prefix,".pdf",sep="")
pdf(outfile, width=9,height=6)
par(mfrow=c(1,2))
h1<-hist(l1,breaks=50,plot=F)
x1<-h1$mids
y1<-h1$counts
fit1<-lm(log(y1[1:25])~x1[1:25])
b1<-fit1$coefficients[1]
a1<-fit1$coefficients[2]
yf1<-exp(a1*x1+b1)
hist(l1,breaks=50,xlab="Length",main="Ancestral Population 1")
points(x1,yf1,type="l",col="red")
legend("topright",paste("Fitted line\ny = exp(",signif(a1),"*x + ",signif(b1),")",sep=""),lty=1,col="red",bty="n")
h2<-hist(l2,breaks=50,plot=F)
x2<-h2$mids
y2<-h2$counts
fit2<-lm(log(y2[1:25])~x2[1:25])
b2<-fit2$coefficients[1]
a2<-fit2$coefficients[2]
yf2<-exp(a2*x2+b2)
hist(l2,breaks=50,xlab="Length",main="Ancestral Population 2")
points(x2,yf2,type="l",col="red")
legend("topright",paste("Fitted line\ny = exp(",signif(a2),"*x + ",signif(b2),")",sep=""),lty=1,col="red",bty="n")
dev.off()
