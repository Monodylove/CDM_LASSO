produceX <- function(n,p){
  #set.seed(999)
  rho=0.2
  Sigma <-matrix(1,p,p) 
  Sigma <- rho^(abs(col(Sigma)-row(Sigma)))
  
  Theta <- c(1:p)
  Theta[1] <- log(1/2)
  Theta[2] <- log(1)
  Theta[3] <- log(3/2)
  Theta[4] <- log(2)
  Theta[5] <- log(5/2)
  Theta[6:p] <- 0
  
  library(MASS)
  Z <- mvrnorm(n, Theta, Sigma)
  X=Z
  return(X)
}
produceY <- function(X,n,p){
  #set.seed(999)
  beta <- rep(0,p)
  beta[1] <- 1
  beta[2] <- -0.8
  beta[3] <- 0.6
  beta[5] <- -1.5
  beta[6] <- -0.5
  beta[7] <- 1.2
  sigma=1/2
  epsilon <- rnorm(n,0,sigma)
  Y=X%*%beta+epsilon
  return(Y)
}

n <- 50
p <- 20

X=produceX(n,p)
Y=produceY(X,n,p)

library(Rcpp)
setwd("E:\\scientific research\\CDM_LASSO")
sourceCpp("CDM_LASSO.cpp")

beta <- rep(0,p)
beta[1] <- 1
beta[2] <- -0.8
beta[3] <- 0.6
beta[5] <- -1.5
beta[6] <- -0.5
beta[7] <- 1.2

sigma=1/2
lambdavec=seq(0.001,sqrt(n)*sigma^2,by=0.001)/10.0

output5=BIC(Y,X,lambdavec)
output7=AIC(Y,X,lambdavec)
output9=GCV(Y,X,lambdavec)
output11=GIC(Y,X,lambdavec)

lambda=lambdavec[which.min(output5)]
lambda2=lambdavec[which.min(output7)]
lambda3=lambdavec[which.min(output9)]
lambda4=lambdavec[which.min(output11)]

output6=CDM_Lasso(Y,X,lambda)#BIC
output8=CDM_Lasso(Y,X,lambda2)#AIC
output10=CDM_Lasso(Y,X,lambda3)#GCV
output12=CDM_Lasso(Y,X,lambda4)#GIC

par(mfrow=c(2,2))
plot(lambdavec,output5,type="l",ylab = "BIC")
plot(lambdavec,output7,type="l",ylab = "AIC")
plot(lambdavec,output9,type="l",ylab = "GCV")
plot(lambdavec,output11,type="l",ylab = "GIC")
par(mfrow=c(1,1))
print(cbind(beta,output6,output8,output10,output12))

