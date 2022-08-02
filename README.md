# OpenGL

该仓库是自己在学习OpenGL过程中一些程序（或是作业？），在此留作记录。

LearnOpenGL_1~5分别为基础部分（最最基础...）、模型、测试、高级光照和PBR，LearnOpenGL_Game是一个简单的2D小游戏，并封装了一个简单的动画状态机（相当简单...简陋），有的项目下有多个功能（有些功能未激活，稍作修改激活即可），shader文件存放在每个项目下的ShaderSourceCode文件夹下。

Model文件夹存放了用到的模型，image文件存放了用到的图片，OpenGLLibrary文件夹下是用到的第三方库。

将库和shader文件的位置配置好，对于需要加载模型的程序把assimpd.dll与生成的可执行文件放入同一文件夹下即可运行。