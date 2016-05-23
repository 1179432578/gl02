gl02 2d enginer

下面是实现一个矩阵栈、矩阵操作函数
实现精灵移动 精灵旋转 缩放
实现窗口适配

矩阵变换分析：
第一步void CCDirector::setProjection(ccDirectorProjection kProjection) 设置了modelview矩阵
projection矩阵 因此命名为setProjection不合理。这些矩阵存放在相应的栈中了，最后当前栈是modelview栈

第二步 void CCNode::visit()中kmGLPushMatrix()把当前栈顶矩阵拷贝一份压入栈中，如果还没初始化就进行初始化
把单位矩阵压入3个栈中
void kmGLPushMatrix(void)
{
kmMat4 top;

lazyInitialize(); //Initialize the stacks if they haven't been already 下面初始化代码

//Duplicate the top of the stack (i.e the current matrix)
kmMat4Assign(&top, current_stack->top);
km_mat4_stack_push(current_stack, &top);
}

void lazyInitialize()
{

if (!initialized) {
kmMat4 identity; //Temporary identity matrix

//Initialize all 3 stacks
//modelview_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
km_mat4_stack_initialize(&modelview_matrix_stack);

//projection_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
km_mat4_stack_initialize(&projection_matrix_stack);

//texture_matrix_stack = (km_mat4_stack*) malloc(sizeof(km_mat4_stack));
km_mat4_stack_initialize(&texture_matrix_stack);

current_stack = &modelview_matrix_stack; 目前操作栈就是modelview栈
initialized = 1;

kmMat4Identity(&identity);

//Make sure that each stack has the identity matrix
km_mat4_stack_push(&modelview_matrix_stack, &identity);
km_mat4_stack_push(&projection_matrix_stack, &identity);
km_mat4_stack_push(&texture_matrix_stack, &identity);
}
}

visit中的transform()是计算模型视图矩阵，然后压入当前栈中，即压入modelview栈中
void CCNode::visit()
{
// quick return if not visible. children won't be drawn.
if (!m_bVisible)
{
return;
}
kmGLPushMatrix();

if (m_pGrid && m_pGrid->isActive())
{
m_pGrid->beforeDraw();
}

this->transform();
...
}

最后draw绘制精灵的时候计算出变换矩阵，然后设置着色器的矩阵变量值
void CCGLProgram::setUniformsForBuiltins()
{
kmMat4 matrixP;
kmMat4 matrixMV;
kmMat4 matrixMVP;

kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);

kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

setUniformLocationWithMatrix4fv(m_uUniforms[kCCUniformPMatrix], matrixP.mat, 1);
setUniformLocationWithMatrix4fv(m_uUniforms[kCCUniformMVMatrix], matrixMV.mat, 1);
setUniformLocationWithMatrix4fv(m_uUniforms[kCCUniformMVPMatrix], matrixMVP.mat, 1);