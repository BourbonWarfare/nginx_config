# Homepage configuration.
server {
    listen       443 ssl;
    server_name aar.bourbonwarfare.com aar.bwarma.com;
    http2 on;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name aar.bourbonwarfare.com aar.bwarma.com;

    port_in_redirect off;

    root B:/web/ocap/static/;
    
    location / {
        proxy_pass  http://127.0.0.1:5000;
    }
}