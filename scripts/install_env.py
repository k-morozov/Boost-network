import os
from sys import platform
import requests
import tarfile
import subprocess as sub

boost_version_major = 1
boost_version_minor = 73
boost_version_patch = 0

class LinuxBoostInstaller:
  def install(self, path):
    command_1 = "cd " + path
    command_2 = "sudo ./bootstrap.sh --prefix=/usr/local"
    command_3 = "sudo ./b2 link=static runtime-link=shared install"
    os.system("{} && {} && {}".format(command_1, command_2, command_3))

class Win32BoostInstaller:
  def install(self, path):
    command_1 = "cd " + path
    command_2 = "bootstrap.bat"
    command_3 = "b2.exe link=static runtime-link=shared install"
    command_4 = "setx /m BOOST_ROOT C:\\Boost\\"
    command_5 = "setx /m BOOST_INCLUDEDIR C:\\Boost\\include\\boost_{}_{}_{}\\".format(boost_version_major, boost_version_minor, boost_version_patch)
    os.system("{} && {} && {} && {} && {}".format(command_1, command_2, command_3, command_4, command_5))
    

def MakeBoostInstaller(platform):
  if platform == "linux":
    return LinuxBoostInstaller()
  elif platform == "win32":
    return Win32BoostInstaller()

print("Platform: " + platform)

boost_filename = "boost_{}_{}_{}.tar.gz".format(boost_version_major, boost_version_minor, boost_version_patch)
boost_url = "https://sourceforge.net/projects/boost/files/boost/{}.{}.{}/{}/download".format(boost_version_major, boost_version_minor, boost_version_patch, boost_filename)

print("Download boost . . .")

r = requests.get(boost_url, allow_redirects=True)

open(boost_filename, "wb+").write(r.content)

print("Unzip boost . . .")

tar = tarfile.open(boost_filename, "r:gz")
tar.extractall()
tar.close()

print("Install boost . . .")

boost_installer = MakeBoostInstaller(platform)

boost_dir = os.getcwd() + "/boost_{}_{}_{}".format(boost_version_major, boost_version_minor, boost_version_patch)
boost_installer.install(boost_dir)

print("Finish")