import { Component, signal } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Device } from './device/device';
import { Router } from './router/router';


@Component({
  selector: 'app-root',
  imports: [RouterOutlet, Device, Router],
  templateUrl: './app.html',
  styleUrl: './app.css'
})
export class App {
  protected readonly title = signal('project-smth');
}
