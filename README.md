# C3D
AustinVan:
begin

1.the example that I have implement successfully is in the examples/c3d_finetuning
run "sh ucf101_testing.sh" in that location, the shell will run the C3D program

2.to change the model(CPU or GPU), you need to change the information in ucf101_testing.sh
 
3.due to the limited memory of my GPU, I have decreased the batch size(you can also increase the size you want in c3d_ucf101_finetuning_test.prototxt)

4.to have a better understand of the C3D architecture I have revised the source code so that there are additional information when program runs.
  if you don't want the information, you can delete them in the corresponding code

end

C3d is a modified version of BVLC caffe to support 3D convolution and pooling.
The main supporting features include:<br/>
- Training or fine-tuning 3D ConvNets.<br/>
- Extracting video features with pre-trained C3D models.<br/>

For more information about c3d, please refer to the [C3D project website](http://www.cs.dartmouth.edu/~dutran/c3d).<br/>

For general questions about Caffe, please refer to the [BVLC project website](http://caffe.berkeleyvision.org) for all documentation.
# Rainman_C3D
# IC_Project
