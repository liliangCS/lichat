> 开发环境：

> 系统：Ubuntu22.04.4

> Qt版本：5.14.2

> QtCreator版本：4.11.1

# 问题日志

### 2024-06-29

**运行报错：**

```cmd
qt.network.ssl: QSslSocket: cannot resolve EVP_PKEY_base_id
qt.network.ssl: QSslSocket: cannot resolve SSL_get_peer_certificate
```
**原因：**

本地OpenSSL版本与Qt支持的OpenSSL版本不一致。

**解决方案：**

代码中通过`qDebug() << QSslSocket::sslLibraryBuildVersionString();`可以获取Qt支持的OpenSSL版本，然后从[OpenSSL官网](https://www.openssl.org/source/old/index.html)下载对应版本进行编译。编译得到的动态库（libssl.so和libcrypto.so）加入到Qt库文件目录中即可。