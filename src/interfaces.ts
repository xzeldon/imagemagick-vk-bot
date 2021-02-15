export interface IImageMagick {
	jpeg(imagePath: string, cb: Function): Buffer
	liquid(imagePath: string, imageType: string, delay: number): Buffer
}
