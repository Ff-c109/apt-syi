# apt-syi
Quickly complete apt installation or repair

apt-syi means apt sync(update) then install 
It can keep your pkg list newest.

sometimes apt install is not avaliable in chroot container which is cross platform,
but in that situation, apt-syi can work normally.

# Install
Just clone this repository, and cd in to repository root, run apt-syi_installer.sh with root.

# Online Install

## Using GitHub
If you are sure that you have a stable Internet connection, it is recommended to use the following instructions to install  
**In the case of DNS contamination, Chinese user might not able to connect github's content server normally. Try [Proprietary Server](#l0)**

```bash
sudo su -c "bash -c '. <(curl -s https://raw.githubusercontent.com/Ff-c109/apt-syi/main/apt-syi_installer-online.sh)'"
```

<div id="l0"></div>
## Using Proprietary Server (Highly Recommend)
This way is the simplest and fastest. But you may need IPv6 network to access it.  
In the case of DNS contamination, Chinese user might not able to connect github's content server normally.
In that situation, Proprietary Server might be helpfull.  
Any way, Try this one first.

```bash
sudo su -c "bash -c '. <(curl -s http://ff-c109.dns.navy/apt-syi/apt-syi_installer-online.sh)'"
```
