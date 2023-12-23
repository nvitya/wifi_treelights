#include "http_app.h"
#include "WebServer.h"
#include "lights_control.h"

WebServer httpsvr(80);

void send_main_page()
{
  unsigned n;

  if (httpsvr.hasArg("MODE"))
  {
    int newmode = httpsvr.arg("MODE").toInt();
    lights.SelectMode(newmode);
    lights.SaveSettings();
  }

  String s = "<!DOCTYPE html> <html>\n";
  s +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  s +="<title>Christmas Tree Lights</title>\n";
  s +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  s +="body{margin-top: 10px;} h1 {color: #444444;margin: 10px auto 10px;} h3 {color: #444444;margin-bottom: 10px;}\n";
  s +=".button {display: block;width: 300px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 18px;margin: 0px auto 10px;cursor: pointer;border-radius: 20px;}\n";
  s +=".button-on {background-color: #3498db;}\n";
  s +=".button-on:active {background-color: #2980b9;}\n";
  s +=".button-off {background-color: #34495e;}\n";
  s +=".button-off:active {background-color: #2c3e50;}\n";
  s +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  s +="</style>\n";
  s +="</head>\n";
  s +="<body>\n";

  s +="<h1>Christmas Tree Lights</h1>\n";
  
  for (n = 0; n < lights.mode_count; ++n)
  {
    TLightModeBase * lmode = lights.mode_list[n];
    String cs;    
    if (n == lights.mode_index)
    {
      cs = "button button-on";
    }
    else
    {
      cs = "button button-off";
    }

    //s +="<p><a class=\""+cs+"\" href=\"/?MODE="+String(n)+"\">"+lmode->name+"</a></p>\n";
    s +="<a class=\""+cs+"\" href=\"/?MODE="+String(n)+"\">"+lmode->name+"</a>\n";
  }

  s +="</body>\n";
  s +="</html>\n";

  httpsvr.send(200, "text/html", s);
}

void handle_not_found()
{
  httpsvr.send(404, "text/plain", "Not found");
}

void http_app_init()
{
  httpsvr.on("/",          send_main_page);
  httpsvr.onNotFound(handle_not_found);

  httpsvr.begin();
}

void http_app_run()
{
  httpsvr.handleClient();
}
