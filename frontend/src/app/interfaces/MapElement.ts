import { output, ElementRef, Component } from "@angular/core";
import { CdkDragEnd } from "@angular/cdk/drag-drop";
import { IPosition } from "./IPosition";

@Component({template: ''})
export class MapElement {
  position = output<IPosition>();

  constructor(private el: ElementRef) {}

  ngAfterViewInit() {
    this.position.emit(this.getCurrentPosition());
  }

  onDrag() {
    this.position.emit(this.getCurrentPosition());
  }

  getCurrentPosition(){
    const rect = this.el.nativeElement.getBoundingClientRect();
    const parentRect = this.el.nativeElement.parentElement.getBoundingClientRect();
    const pos = {
      x: rect.left - parentRect.left + rect.width / 2,
      y: rect.top - parentRect.top + rect.height / 2
    };
    return pos;
  }
}