在R中键入“sourceCpp("CDM_LASSO.cpp")”即可将本程序中的部分函数导入至R。
Type "sourceCpp("CDM_LASSO.cpp")" in R to import some functions in this program into R. 

可输出函数：
Output function: 

① CDM_Lasso: 
    使用方法：  CDM_Lasso(因变量向量Y，自变量矩阵X，参数λ)
    输出：基于坐标下降法的参数β的估计值
    How to use: CDM_Lasso (dependent variable vector Y, independent variable matrix X, parameter λ)
    Output: Estimated value of parameter β based on coordinate descent 

②BIC：
   使用方法：  BIC(因变量向量Y，自变量矩阵X，参数向量λ)
   输出：向量λ中每个元素作为惩罚参数所估计得出的向量β对应的BIC取值。即输出结果为BIC取值的向量。
   How to use: BIC (dependent variable vector Y, independent variable matrix X, parameter vector λ)
   Output: The BIC value corresponding to the vector β estimated by each element in the vector λ as the penalty parameter. That is, the output result is a vector of BIC values. 

③AIC：
   使用方法：  AIC(因变量向量Y，自变量矩阵X，参数向量λ)
   输出：向量λ中每个元素作为惩罚参数所估计得出的向量β对应的AIC取值。即输出结果为AIC取值的向量。
   How to use: AIC (dependent variable vector Y, independent variable matrix X, parameter vector λ)
   Output: The AIC value corresponding to the vector β estimated by each element in the vector λ as the penalty parameter. That is, the output result is a vector of AIC values. 

④GCV：
   使用方法：  GCV(因变量向量Y，自变量矩阵X，参数向量λ)
   输出：向量λ中每个元素作为惩罚参数所估计得出的向量β对应的GCV取值。即输出结果为GCV取值的向量。
   How to use: GCV (dependent variable vector Y, independent variable matrix X, parameter vector λ)
   Output: The GCV value corresponding to the vector β estimated by each element in the vector λ as the penalty parameter. That is, the output result is a vector of GCV values. 

⑤GIC：
   使用方法：  GIC(因变量向量Y，自变量矩阵X，参数向量λ)
   输出：向量λ中每个元素作为惩罚参数所估计得出的向量β对应的GIC取值。即输出结果为GIC取值的向量。
   How to use: GIC (dependent variable vector Y, independent variable matrix X, parameter vector λ)
   Output: The GIC value corresponding to the vector β estimated by each element in the vector λ as the penalty parameter. That is, the output result is a vector of GIC values. 


不可输出函数(内部调用函数)：
Non-exportable functions (internally called functions): 

① d: 
    使用方法：  d(参数向量β)
    输出：参数向量β中非零元素的个数
    How to use: d (parameter vector β)
    Output: the number of non-zero elements in the parameter vector β 

② Max: 
    使用方法：  Max(数值x,数值y)
    输出：x与y中的最大值
    How to use: Max(value x, value y)
    output: the maximum value of x and y 

③sgn: 
    使用方法：  sgn(数值x)
    输出：符号函数。x若大于0则输出1，x小于零则输出-1，x等于0输出0
    How to use: sgn(number x)
    Output: Symbolic function. If x is greater than 0, output 1, if x is less than 0, output -1, if x is equal to 0, output 0 

④ Soft: 
    使用方法：  Soft(数值t，数值λ)
    输出：输出对应的soft-threshold值。即sgn(t)* Max(fabs(t)-lambda,0)
    How to use: Soft(value t, value λ)
    Output: Output the corresponding soft-threshold value. i.e. sgn(t)*Max(fabs(t)-lambda,0) 




