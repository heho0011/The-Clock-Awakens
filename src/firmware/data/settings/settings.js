function showLoadingMessage() {

    $("#alert")
        .removeClass("alert-info alert-danger")
        .addClass("alert-info")
        .text("Loading...");
}

$(function() {
    showLoadingMessage();
    $("form *").prop("disabled", true);
});

$("#save-button").click(showLoadingMessage);

$("#brightness-slider").on("input", function() {
    $("#brightness-value").text($(this).val() + "%");
});

$("#night-mode-brightness-slider").on("input", function() {
    $("#night-mode-brightness-value").text($(this).val() + "%");
});

$.ajax("get").done(function(settings) {

    // Display the settings on the page
    $("#tz").val(settings.timezone);
    $("#brightness-slider").val(settings.brightness);
    $("#brightness-value").text(settings.brightness + "%");
    $("#hour-color").val(settings.hour_color);
    $("#minute-color").val(settings.minute_color);
    $("#second-color").val(settings.second_color);
    $("#animation").val(settings.animation);
    $("#night-mode-enable").val(settings.night_mode.enabled);
    $("#night-mode-brightness-slider").val(settings.night_mode.brightness);
    $("#night-mode-brightness-value").text(settings.night_mode.brightness + "%");
    $("#gamma").val(settings.gamma);

    $("form *").prop("disabled", false);

    // Display the relevant alert if necessary
    if (location.search.indexOf("status=success") != -1) {

        $("#alert")
            .removeClass("alert-info")
            .addClass("alert-success")
            .text("Settings saved successfully!");

    } else if (location.search.indexOf("status=error") != -1) {

        $("#alert")
            .removeClass("alert-info")
            .addClass("alert-danger")
            .text("An error occurred when saving the settings.");

    } else {

        $("#alert")
            .removeClass("alert-info")
            .text("");
    }
});