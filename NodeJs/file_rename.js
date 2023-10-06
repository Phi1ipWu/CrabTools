const fs = require('fs');
const path = require('path');

const DIR_PATH = "E:/AliyunDrivers/AC01-图灵程序设计丛书";
const SRC_NAME = "[图灵程序设计丛书].";
const DST_NAME = "";

function readDirectory(dir) {
  fs.readdir(dir, (err, files) => {
    if (err) {
      console.error(err);
      return;
    }

    for (const file of files) {
      const filePath = path.join(dir, file);

      fs.stat(filePath, (err, stat) => {
        if (err) {
          console.error(err);
          return;
        }

        if (stat.isDirectory()) {
          readDirectory(filePath);
        }
        else if (stat.isFile()) {
          console.log(filePath.replace(SRC_NAME, DST_NAME));
          fs.rename(filePath, filePath.replace(SRC_NAME, DST_NAME), (err) => {
            console.error(err);
          });
        }
      });
    }
  });
}

readDirectory(DIR_PATH);
