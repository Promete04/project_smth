import { Component, signal } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Device } from './device/device';

@Component({
  selector: 'app-root',
  imports: [RouterOutlet, Device],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  protected readonly title = signal('project-smth');
}
