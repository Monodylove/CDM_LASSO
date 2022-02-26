// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]

#include <RcppArmadillo.h>
#include<math.h>

using namespace Rcpp;
using namespace arma;

mat CDM_Lasso(vec Y,mat Z,double lambda);
double Max(double x,double y);
int sgn(double d);
vec Soft(double t,double lambda);
vec d(vec Beta);
vec AIC(vec Y,mat Z,vec Lambda);
vec BIC(vec Y,mat Z,vec Lambda);
vec GIC(vec Y,mat Z,vec Lambda);
vec GCV(vec Y,mat Z,vec Lambda);

// [[Rcpp::export]]
mat CDM_Lasso(vec Y,mat Z,double lambda) {//Z _n*p  Y_n*1   beta_p*1
  int n=Y.n_elem;
  int p=Z.n_cols;
  int j;
  vec Betav=ones<vec>(p);
  vec Beta=zeros<vec>(p);
  vec bPz=zeros<vec>(n);
  vec res(n);
  uvec k(1);
  mat ZT=Z.t();
  mat Z2(1,p);
  double epsilon=0.001;
  Z2=sum(Z%Z,0)/1.0/n;
  
  while(accu(abs(Betav-Beta))>epsilon){
    Betav=Beta;
    for(j=0;j<p;j++){
      bPz=Z*Beta-Z.col(j)*Beta(j);
      res=Y-bPz;
      k=j;// X.elem(uvec)=vec
      Beta.elem(k)=Soft(sum(res.t()*Z.col(j))/(1.0*n),(lambda))/Z2(0,j);
    }
  }
  return Beta;
}

// [[Rcpp::export]]
vec BIC(vec Y,mat Z,vec Lambda){
  double lambda;
  double L2;
  int i;
  int n=Y.n_elem;
  int m=Lambda.n_elem;
  uvec k(1);
  vec Beta;
  vec BIC=zeros<vec>(m);
  vec out(1);
  
  for(i=0;i<m;i++){
    lambda=Lambda(i);
    Beta=CDM_Lasso(Y,Z,lambda);
    L2=norm( Y-Z*Beta);
    k=i;
    out={1.0*log(L2*L2/(1.0*n))+1.0*log(1.0*n)*d(Beta)/n};
    BIC.elem(k)=out;
  }
  return  BIC;
}

// [[Rcpp::export]]
vec AIC(vec Y,mat Z,vec Lambda){
  double lambda;
  double L2;
  int i;
  int n=Y.n_elem;
  int m=Lambda.n_elem;
  uvec k(1);
  vec Beta;
  vec AIC=zeros<vec>(m);
  vec out(1);
  
  for(i=0;i<m;i++){
    lambda=Lambda(i);
    Beta=CDM_Lasso(Y,Z,lambda);
    L2=norm( Y-Z*Beta, 2);
    k=i;
    out={(1.0*log(L2*L2/(double)n)+2.0*d(Beta)/(double)n)};
    AIC.elem(k)=out;
  }
  return  AIC;
}

// [[Rcpp::export]]
vec GCV(vec Y,mat Z,vec Lambda){
  double lambda;
  double L2;
  int i;
  int n=Y.n_elem;
  int m=Lambda.n_elem;
  uvec k(1);
  vec Beta;
  vec GCV=zeros<vec>(m);
  vec out(1);
  
  for(i=0;i<m;i++){
    lambda=Lambda(i);
    Beta=CDM_Lasso(Y,Z,lambda);
    L2=norm( Y-Z*Beta, 2);
    k=i;
    out={L2*L2/(1.0*n*(1.0-(d(Beta)/n/1.0))*(1.0-(d(Beta)/n/1.0)))};
    GCV.elem(k)=out;
  }
  return  GCV;
}

// [[Rcpp::export]]
vec GIC(vec Y,mat Z,vec Lambda){
  double lambda;
  double L2;
  int i;
  int n=Y.n_elem;
  int m=Lambda.n_elem;
  int p=Z.n_cols;
  uvec k(1);
  vec Beta;
  vec GIC=zeros<vec>(m);
  vec out(1);
  
  for(i=0;i<m;i++){
    lambda=Lambda(i);
    Beta=CDM_Lasso(Y,Z,lambda);
    L2=norm( Y-Z*Beta, 2);
    k=i;
    out={(log(L2*L2/(double)n)+(d(Beta)-1)*log(Max(p,n))*log(log(n))/(double)n)};
    GIC.elem(k)=out;
  }
  return  GIC;
}

vec d(vec Beta){
  vec B=zeros( Beta.n_elem );
  uvec q1 = find(Beta != B );
  int n=q1.n_elem;
  vec out = {n};
  return out;
}

double Max(double x,double y){
  double t;
  if(x>=y){t=x;}
  else{t=y;}
  return t;
}

int sgn(double d){
  if(d<0){ return -1;}
  else if (d==0) {return 0;}
  else {return 1;}
}

vec Soft(double t,double lambda){
  double temp;
  vec value(1);
  temp=sgn(t)* Max(fabs(t)-lambda,0);
  value=temp;
  return value;
}