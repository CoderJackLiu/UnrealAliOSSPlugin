# AliOSSServer
![image](https://user-images.githubusercontent.com/26760292/175764723-bc01f130-b84e-4968-b83b-e94760f58439.png)

<br> Hi, I am Jack! Glad to see you here!
<br> This is a unreal plugin for interaction with alibaba oss server! You can use it by blueprint with you accesskey directly.The plugin include almost the common usage which supply by alioss server Api.
<br>
<br> This Project is in a period of developing,so there may be some unconvenience. In this plug-in, I created a Functionlib that contains most of the AliOss common methods, but they need to pass in AccessKey and other account info for each method. 
<br>
<br>In normal use, you definitely don't expose AccessKey. Instead, you storeAccessKey in a more discreet way and don't change it often, so you might cache it as a local encryption file or access it through a request server or in a static class or the other way.So you may need modify the plugin in a way that is convenient to you.
<br>
<br>So if you have more good idea ,Please coommit your idea to the issue tab,or send me a email <596770421@qq.com>. Also welcome to join me and create a pullRequest to improve the project.
<br>
<br> Next we are going to develop a simple online game, if you are interested, welcome to join us!

### References
* [AliOSS C++_API](https://help.aliyun.com/document_detail/103184.html)
* [CMake](https://cmake.org/)
* [unreal Third-Party](https://docs.unrealengine.com/5.0/zh-CN/integrating-third-party-libraries-into-unreal-engine/)


### Including：

* Bucket
  * Create
  * Delete
  * Exists
  * List 
* Upload
  * upload a file
  * upload from memory
  * append upload
  * progress
* DownLoad
  * Download to a local file
  * Download to memory
  * Download with progress
  * 
* FileManage
  *  File Exits
  *  File Access Bility Management
  *  List Files
  *  Dlete File
  *  Copy File
  *  Forbidden of overring file with same name
*  Version control
*  Object Tags
*  Data Encryption
*  Speed Control
*  Data Safty
*  Access Authority
*  Image Process

