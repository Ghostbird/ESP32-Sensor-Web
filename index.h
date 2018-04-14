const char * INDEX_HTML = PROGMEM( R"INDEX(
<!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
        <link rel="stylesheet" href="https://code.getmdl.io/1.3.0/material.brown-orange.min.css" />
        <style>
            body{
                width:100%;
                display:flex;
                justify-content: space-around;
                align-items: stretch;
                flex-direction: row;
            }
            @media (max-width: 900px)
            {
                body {
                    flex-direction: column;
                }
            }
            .mdl-card {
                flex: 1 0 0;
                margin:10px;
                float:left;
                width:auto;
            }
            .mdl-card__title {
                background: rgb(121, 85, 72);
                min-height:60px;
                color:white;
            }
            .mdl-card__title-text {
                font-size: 5.5vmin;
            }
            .mdl-card__menu {
                color:white;
            }
            .mdl-card__supporting-text {
                font-size:6vmin;
                line-height:6vmin;
                height:100%;
            }
        </style>
        <script>
            function refreshData() {
                let xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        data = JSON.parse(xhttp.responseText);
                        // Typical action to be performed when the document is ready:
                        document.getElementById("temperature").innerHTML = data.temperature;
                        document.getElementById("humidity").innerHTML = data.humidity;
                        document.getElementById("uptime").innerHTML = data.uptime;
                    }
                };
                xhttp.open("GET", "/sensor", true);
                xhttp.send(); 
            }

            function onLoad() {
                document.body.removeChild(document.getElementById("JSnotice"));
                refreshData();
                window.setInterval(refreshData,2000);
            }
        </script>
    </head>
    <body onload="onLoad()">
        <p id="JSnotice">
            This page uses Javascript to request the sensor data from the server.
            Are you a robot, script, or can you not use JavaScript for another reason?
            Please read the sensor data from <a href="/sensor">here</a>
        </p>
        <div class="mdl-card-wide mdl-card mdl-shadow--2dp">
            <div class="mdl-card__title">
                <h2 class="mdl-card__title-text">
                    Temperature
                </h2>
            </div>
            <div class="mdl-card__supporting-text">
                <span id="temperature"></span><span>℃</span>
            </div>
        </div>
        <div class="mdl-card-wide mdl-card mdl-shadow--2dp">
            <div class="mdl-card__title">
                <h2 class="mdl-card__title-text">
                    Humidity
                </h2>
            </div>
            <div class="mdl-card__supporting-text">
                <span id="humidity"></span><span>%</span>
            </div>
        </div>
        <div class="mdl-card-wide mdl-card mdl-shadow--2dp">
            <div class="mdl-card__title">
                <h2 class="mdl-card__title-text">
                    Uptime
                </h2>
            </div>
            <div class="mdl-card__supporting-text">
                <span id="uptime"></span><span>ms</span>
            </div>
        </div>
    </body>
</html>
)INDEX");

