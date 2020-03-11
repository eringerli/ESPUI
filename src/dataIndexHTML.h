const char HTML_INDEX[] PROGMEM = R"=====(
<!DOCTYPE html><html> <head><meta charset=utf-8><title>Control</title><meta name=viewport content="width=device-width, initial-scale=1"><link rel="shortcut icon" href=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAPFBMVEUAAACA1VWR21qQ2liR3FqR3FqS3VuR3VqR3VuR3VqO21mS21uS3FqS3FqS21uJ2GKQ21qR3FuR3FoAAAB/3Gu7AAAAEnRSTlMABoA3kPBwz8i5Kzioxg4NVcU3uEJHAAAAAWJLR0QAiAUdSAAAAAlwSFlzAAAN1wAADdcBQiibeAAAAAd0SU1FB+EFEhcEM+HpYwQAAABYSURBVBjThY/JDsAgCESt4lpX/v9jLQZJ6qF9t3khAyj1xXUKbQ4BVowDwqOYgExkkW4iY6lPaF06RqM8YItOuRbMaz6xjbsusDAW/drplBg47jP696cXE8bPA1eUDeK2AAAAJXRFWHRkYXRlOmNyZWF0ZQAyMDE3LTA1LTE4VDIzOjA0OjUxKzAyOjAwxE59ewAAACV0RVh0ZGF0ZTptb2RpZnkAMjAxNy0wNS0xOFQyMzowNDo1MSswMjowMLUTxccAAAAZdEVYdFNvZnR3YXJlAHd3dy5pbmtzY2FwZS5vcmeb7jwaAAAAAElFTkSuQmCC><link rel=stylesheet href=/css/normalize.css><link rel=stylesheet href=/css/style.css><script src=/js/zepto.min.js></script><script src=/js/slider.js></script><script src=/js/controls.js></script><script src=/js/tabbedcontent.js></script></head> <body onload=javascript:start();> <div> <h4><div id=mainHeader>Control</div> <span id=conStatus class=label>Offline</span></h4></div> <hr> <div class=container> <div id=row class="row u-full-width"></div> <ul id=tabsnav class="navigation navigation-tabs u-full-width"></ul> <div id=tabscontent class="tabscontent u-full-width"></div> </div> </body> </html> 
)=====";

const uint8_t HTML_INDEX_GZIP[910] PROGMEM = { 31,139,8,0,62,106,105,94,2,255,133,84,109,147,162,56,16,254,43,156,159,238,106,119,6,81,199,153,217,21,171,130,130,51,42,34,32,40,126,11,144,145,96,120,25,18,68,253,245,151,200,204,237,94,237,213,30,85,36,79,186,159,126,186,105,160,71,127,76,173,201,38,88,235,82,194,50,50,30,221,86,105,148,32,24,143,71,25,98,80,138,18,88,81,196,212,154,189,221,61,141,71,12,51,130,198,147,34,103,85,65,70,114,123,108,153,57,204,144,122,194,168,41,139,138,73,17,167,160,156,169,157,6,199,44,81,99,116,194,17,186,187,29,190,74,56,199,12,67,114,71,35,72,144,170,116,198,35,130,243,163,84,33,162,118,104,194,195,163,154,73,152,75,116,164,164,66,111,106,12,25,252,134,51,120,64,114,153,31,190,135,144,162,225,224,43,246,53,203,105,186,139,217,161,0,252,90,185,94,162,123,7,142,52,113,4,246,4,152,98,47,150,246,243,70,0,109,22,107,27,79,7,96,57,91,79,228,115,162,217,220,56,209,82,215,152,175,184,119,56,231,177,135,87,110,92,11,189,9,24,242,53,22,145,86,41,84,135,25,95,140,254,36,170,137,254,36,244,214,134,102,250,186,119,227,42,254,214,233,41,239,118,143,96,167,111,188,139,219,237,251,181,211,247,57,110,119,171,167,100,110,79,169,221,155,143,223,28,207,123,179,133,205,227,56,159,115,12,145,87,147,251,179,250,81,232,235,185,227,110,136,9,180,2,244,143,107,173,185,62,225,135,197,21,23,231,195,96,229,71,94,191,214,231,47,183,39,221,206,151,78,215,6,24,120,177,123,51,144,198,53,200,85,244,68,105,0,152,198,145,102,99,28,162,155,47,238,186,158,98,104,95,116,67,79,34,221,252,242,82,6,141,104,132,22,184,158,163,249,90,186,73,2,121,62,165,224,48,209,93,54,32,229,78,62,61,167,75,123,63,31,190,27,207,172,127,76,192,37,85,206,59,111,17,218,3,205,47,154,105,243,110,5,7,253,124,60,110,7,56,24,146,53,52,186,67,231,221,124,10,94,153,85,59,161,9,175,195,115,26,210,154,78,193,86,142,171,146,104,135,193,99,186,30,62,15,163,157,254,20,174,129,130,188,41,90,244,68,117,243,157,99,108,95,156,99,176,115,136,149,173,46,251,173,209,221,219,224,98,78,245,254,114,3,148,229,70,31,248,211,215,171,149,130,174,149,122,231,197,21,92,56,110,206,250,195,51,106,196,171,240,187,142,159,116,247,51,30,183,41,89,216,115,202,125,126,4,102,10,206,171,75,183,89,185,221,179,101,216,23,243,90,52,171,105,161,152,46,109,204,180,104,204,165,183,57,71,145,40,97,31,235,126,16,27,171,211,62,119,250,193,110,78,192,75,220,143,47,15,101,152,177,107,208,51,154,189,251,112,138,50,20,62,166,13,188,181,84,39,198,230,232,214,118,54,153,252,244,37,83,118,33,136,38,8,177,246,35,150,35,74,229,188,168,50,72,240,21,221,243,211,255,145,111,198,150,72,163,10,151,76,162,85,164,202,41,149,175,168,100,197,125,134,243,251,148,59,229,214,251,11,139,18,28,163,234,183,148,168,253,147,233,111,73,12,134,33,138,63,254,232,127,51,229,219,168,144,70,97,17,95,164,34,39,5,140,213,20,158,96,235,255,70,25,172,216,159,127,125,231,140,24,159,196,100,25,140,5,146,112,172,102,16,231,47,60,26,85,63,230,73,75,162,37,204,5,131,103,116,25,100,53,149,34,2,41,85,9,12,17,25,91,111,111,188,109,136,215,192,105,162,2,46,249,17,152,84,109,162,15,190,168,152,39,65,159,86,46,89,21,205,135,179,35,96,125,247,86,19,210,142,165,206,63,50,53,17,84,254,212,52,135,159,90,29,14,241,1,50,92,228,210,15,120,39,72,191,168,212,228,71,66,65,248,232,220,167,210,207,166,255,46,224,115,19,93,21,123,59,150,255,6,7,151,15,103,173,5,0,0 };
