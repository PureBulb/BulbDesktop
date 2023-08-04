#ifndef COMMON_H
#define COMMON_H

#include <QString>
typedef enum wallpaperType{graph,gif,video} WallpaperType;

#define INI_TYPE "type"
#define INI_GRAPH_PATHS "graph.paths"
#define INI_GIF_PATHS "gif.paths"
#define INI_VIDEO_PATHS "video.paths"
#define INI_GRAPH_DELAY "graph.delay"

const QString typeNames[] = {"图片壁纸","Gif","视频"};

#endif // COMMON_H
