let img_element = new Image();
img_element.src = "images/organic.jpg";
let img_context = document.getElementById('canvas').getContext('2d');
img_context.drawImage(img_element, 0, 0);

let getPixelValue = (x,y) => {
    return img_context.getImageData(x, y, 1, 1).data;
}